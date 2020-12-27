#include <bits/stdc++.h>
#ifdef LOCAL
#include "debuger.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

template<int MOD>
struct Integral {
  int v_ = 0;

  Integral() {}
  Integral(int v) : Integral((long long)v) {}  // Implicit conversion is allowed.
  Integral(long long v) {
    if (v >= MOD) v -= MOD;
    if (v < 0) v += MOD;
    if (v >= MOD || v < 0) v = (v % MOD + MOD) % MOD;
    v_ = v;
  }
  ~Integral() = default;

  int val() const { return v_; }
  Integral operator + (const Integral& rhs) const { return Integral(val() + rhs.val()); }
  Integral operator - (const Integral& rhs) const { return Integral(val() - rhs.val()); }
  Integral operator * (const Integral& rhs) const { return Integral(val() * 1LL * rhs.val()); }
  Integral operator / (const Integral& rhs) const { return *this * rhs.inv(); }
  Integral operator - () const { return Integral(-val()); }
  Integral& operator += (const Integral& rhs) { *this = *this + rhs; return *this; }
  Integral& operator -= (const Integral& rhs) { *this = *this - rhs; return *this; }
  Integral& operator *= (const Integral& rhs) { *this = *this * rhs; return *this; }
  Integral& operator /= (const Integral& rhs) { *this = *this / rhs; return *this; }
  bool operator == (const Integral& rhs) { return val() == rhs.val(); }
  bool operator != (const Integral& rhs) { return !(*this == rhs); }

  Integral power(long long b) const {
    long long ret = 1 % MOD, a = v_;
    for ( ; b; b >>= 1, a = a * a % MOD) if (b & 1) ret = ret * a % MOD; return ret;
  }
  Integral inv() const { return power(MOD - 2); }
};

template<int MOD>
struct Binomial {
  std::vector<Integral<MOD>> factor, inv_factor;

  void init(int n) {
    factor.resize(n + 1);
    inv_factor.resize(n + 1);
    factor[0] = 1;
    for (int i = 1; i <= n; ++i) factor[i] = factor[i - 1] * i;
    inv_factor[n] = factor[n].inv();
    for (int i = n; i >= 1; --i) inv_factor[i - 1] = inv_factor[i] * i;
  }

  Integral<MOD> operator () (int a, int b) const {
    if (a < b || b < 0) return 0;
    if (a < factor.size()) return factor[a] * inv_factor[b] * inv_factor[a - b];
    b = std::min(b, a - b);
    Integral<MOD> ret = 1;
    for (int i = 1; i <= b; ++i) ret = ret * (a + 1 - i) / i;
    return ret;
  }
};

void test_binomial() {
  const int MOD = 998244353;
  using Binom = Binomial<MOD>;
  Binom binom;
  binom.init(100);
  CHECK(1 == binom(99, 0).val());
  CHECK(0 == binom(99, 10000).val());
  CHECK(4950 == binom(100, 2).val());
  CHECK(19900 == binom(200, 2).val());
  CHECK(binom(200000, 2) == binom(200000, 199998));
}

int main() {
  test_binomial();
}