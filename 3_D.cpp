#include <cmath>
#include <iostream>
#include <map>

int64_t PowMod(int64_t a, int64_t b, int64_t m) {
  int64_t res = 1;
  while (b > 0) {
    if ((b & 1) != 0) {
      res = (res * a) % m;
      --b;
    } else {
      a = (a * a) % m;
      b >>= 1;
    }
  }
  return res % m;
}

int64_t Solve(int64_t a, int64_t b, int64_t m) {
  int64_t n = static_cast<int64_t>(sqrt(m) + 1.0);
  std::map<int64_t, int64_t> vals;

  for (int64_t i = n; i >= 1; --i) {
    vals[PowMod(a, i * n, m)] = i;
  }

  int64_t min_ans = __INT_MAX__;
  for (int64_t i = 0; i <= n; ++i) {
    int64_t cur = (PowMod(a, i, m) * b) % m;
    if (vals.contains(cur)) {
      int64_t ans = vals[cur] * n - i;
      if (ans < m) {
        min_ans = std::min(min_ans, ans);
      }
    }
  }
  if (min_ans != __INT_MAX__) {
    return min_ans;
  }
  return -1;
}

int main() {
  int64_t a;
  int64_t b;
  int64_t m;
  while (std::cin >> m >> a >> b) {
    int64_t result = Solve(a, b, m);
    if (result == -1) {
      std::cout << "no solution\n";
    } else {
      std::cout << result << "\n";
    }
  }
  return 0;
}
