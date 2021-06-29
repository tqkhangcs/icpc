#include <bits/stdc++.h>

using namespace std;

constexpr int inf = int(1e9) + 10;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  while (cin >> n >> m) {
    if (n == 0 && m == 0) {
      break;
    }
    assert(n * m <= 1e6);
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    deque<array<int, 2>> dq;
    vector<vector<int>> dis(n, vector<int>(m, -1));
    for (int i = 0; i < n; ++i) { // row i, col 0
      if (a[i][0] != '@') { // magic immune
        int cost = (a[i][0] == '.');
        if (cost) { // normal
          dq.push_back({i, 0});
        } else { // wall
          dq.push_front({i, 0});
        }
        dis[i][0] = cost;
      }
    }
    for (int j = 0; j < m; ++j) { // row r - 1, col j
      if (a[n - 1][j] != '@' && dis[n - 1][j] == -1) {
        int cost = (a[n - 1][j] == '.');
        if (cost) {
          dq.push_back({n - 1, j});
        } else {
          dq.push_front({n - 1, j});
        }
        dis[n - 1][j] = cost;
      }
    }
    constexpr int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    constexpr int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    cout << ([&]() {
      while (not dq.empty()) {
        array<int, 2> cur = dq.front();
        int x = cur[0], y = cur[1];
        dq.pop_front();
        if (x == 0 || y == m - 1) {
          return dis[x][y];
        }
        for (int i = 0; i < 8; ++i) {
          int nx = x + dx[i];
          int ny = y + dy[i];
          if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
          if (dis[nx][ny] != -1 || a[nx][ny] == '@') continue; // magic immune
          int cost = (a[nx][ny] == '.');
          if (cost) { // normal
            dq.push_back({nx, ny});
          } else { // wall
            dq.push_front({nx, ny});
          }
          dis[nx][ny] = dis[x][y] + cost;
        }
      }
      return -1;
    }()) << '\n';
  }
  return 0;
}
