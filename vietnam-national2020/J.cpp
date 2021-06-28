#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  vector<int> h(n);
  for (int i = 0; i < n; ++i) {
    cin >> h[i];
  }
  auto Get = [&]() {
    vector<int> stk;
    vector<long long> pref(n);
    pref[0] = h[0];
    for (int i = 0; i < n; ++i) {
      while (int(stk.size()) >= 2 && h[stk.end()[-2]] >= h[stk.end()[-1]] && h[stk.end()[-1]] < h[i]) {
        stk.pop_back();
      }
      stk.push_back(i);
      if (i > 0) {
        pref[i] = pref[i - 1] + h[i];
      }
    }
    long long res = 0;
    for (int i = 0; i + 1 < int(stk.size()); ++i) {
      int mn = min(h[stk[i]], h[stk[i + 1]]);
      int dis = stk[i + 1] - stk[i] - 1;
      res += (long long) mn * dis - ((long long) pref[stk[i + 1] - 1] - pref[stk[i]]);
    }
    return res;
  };
  long long ans = 0;
  function<void(int, int)> Solve = [&](int i, int cur) {
    if (cur == 0) {
      ans = max(ans, Get());
      return;
    }
    if (i == n - 1) {
      h[i] += cur;
      ans = max(ans, Get());
      h[i] -= cur;
      return;
    }
    for (int j = 0; j <= cur; ++j) {
      h[i] += j;
      Solve(i + 1, cur - j);
      h[i] -= j;
    }
  };
  Solve(0, k);
  cout << ans << '\n';
  return 0;
}
