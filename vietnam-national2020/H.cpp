#include <bits/stdc++.h>

using namespace std;

constexpr int P = 1000000007;

inline void add(int &a, int b) {
  a += b;
  if (a >= P) {
    a -= P;
  }
}

inline void sub(int &a, int b) {
  a -= b;
  if (a < 0) {
    a += P;
  }
}

inline int mul(int a, int b) {
  return int(1ll * a * b % P);
}

inline int power(int a, long long b) {
  int res = 1;
  while (b) {
    if (b & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

inline int inv(int a) {
  a %= P;
  if (a < 0) {
    a += P;
  }
  int b = P, u = 0, v = 1;
  while (a) {
    int t = b / a;
    b -= t * a;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  assert(b == 1);
  if (u < 0) {
    u += P;
  }
  return u;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> w(n);
    for (int i = 0; i < n; ++i) {
      cin >> w[i];
    }
    map<int, map<int, int>> dict;
    vector<string> hidden_message;
    int d;
    cin >> d;
    for (int i = 0; i < d; ++i) {
      string s;
      cin >> s;
      int len = int(s.size());
      dict[len][s[0] - 'a']++;
      if (len == n) {
        hidden_message.push_back(s);
      }
    }
    int ans = 0;
    for (string s : hidden_message) {
      int res = 1;
      dict[n][s[0] - 'a']--;
      for (int i = 0; i < n; ++i) {
        res = mul(res, max(0, dict[w[i]][s[i] - 'a']));
        dict[w[i]][s[i] - 'a']--;
      }
      for (int i = 0; i < n; ++i) {
        dict[w[i]][s[i] - 'a']++;
      }
      add(ans, res);
      dict[n][s[0] - 'a']++;
    }
    cout << ans << '\n';
  }
  return 0;
}
