#ifndef TIFA_LIBS_MATH_EULER_PHI_U32
#define TIFA_LIBS_MATH_EULER_PHI_U32

#include "isqrt.hpp"

namespace tifa_libs::math {

constexpr u32 euler_phi_u32(u32 n) {
  u32 ans = n;
  for (u32 i = 2; i <= isqrt(n); ++i)
    if (!(n % i)) {
      ans = ans / i * (i - 1);
      while (!(n % i)) n /= i;
    }
  if (n > 1) ans = ans / n * (n - 1);
  return ans;
}

}  // namespace tifa_libs::math

#endif