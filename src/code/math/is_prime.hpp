#ifndef TIFA_LIBS_MATH_IS_PRIME
#define TIFA_LIBS_MATH_IS_PRIME

#include "../bit/cntr0.hpp"
#include "mul_mod_u.hpp"
#include "qpow_mod.hpp"

namespace tifa_libs::math {

constexpr bool is_prime(u64 n) {
  if (n <= 2) return n == 2;
  if (~n & 1) return false;
  if (n < 8 || n == 61) return true;

  auto f = [n, d = (n - 1) >> bit::cntr0(n - 1)](auto const& bases) -> bool {
    for (u64 i : bases) {
      if (!(i % n)) continue;
      u64 t = d, y = qpow_mod(i, t, n);
      while (t != n - 1 && y != 1 && y != n - 1) {
        y = mul_mod_u(y, y, n);
        t *= 2;
      }
      if (y != n - 1 && (~t & 1)) return false;
    }
    return true;
  };

  if (n < (1 << 30)) {
    constexpr u64 bases[3] = {2, 7, 61};
    return f(bases);
  }
  constexpr u64 bases[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  return f(bases);
}

}  // namespace tifa_libs::math

#endif