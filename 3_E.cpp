#include <iostream>

long long ModExp(long long base, long long exp, long long mod) {
  long long result = 1;
  base %= mod;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % mod;
    }
    base = (base * base) % mod;
    exp /= 2;
  }
  return result;
}

int Get(long long a, long long p) {
  return ModExp(a, (p - 1) / 2, p) == p - 1 ? -1 : 1;
}

long long Solve(long long a, long long p) {
  if (a == 0) {
    return 0;
  }

  if (p == 2) {
    return a;
  }

  if (Get(a, p) != 1) {
    return -1;
  }

  long long q = p - 1;
  long long s = 0;
  while ((q & 1) == 0) {
    q >>= 1;
    ++s;
  }

  if (s == 1) {
    return ModExp(a, (p + 1) / 4, p);
  }

  long long z = 2;
  while (Get(z, p) != -1) {
    ++z;
  }

  long long m = s;
  long long c = ModExp(z, q, p);
  long long t = ModExp(a, q, p);
  long long r = ModExp(a, (q + 1) / 2, p);

  while (t != 1) {
    long long temp = t;
    long long i = 0;
    for (i = 0; i < m; ++i) {
      if (temp == 1) {
        break;
      }
      temp = (temp * temp) % p;
    }
    long long b = (m - i - 1 >= 0) ? ModExp(c, 1LL << (m - i - 1), p) : 1;

    m = i;
    c = (b * b) % p;
    t = (t * c) % p;
    r = (r * b) % p;
  }
  return r;
}

int main() {
  int t;
  std::cin >> t;
  while (t-- != 0) {
    long long a;
    long long p;
    std::cin >> a >> p;
    long long result = Solve(a, p);
    if (result == -1) {
      std::cout << "IMPOSSIBLE\n";
    } else {
      std::cout << result << "\n";
    }
  }
  return 0;
}