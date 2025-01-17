#ifndef TIFA_LIBS_MATH_LINEAR_MPF_SEIVE
#define TIFA_LIBS_MATH_LINEAR_MPF_SEIVE

#include "linear_seive.hpp"

namespace tifa_libs::math {

inline vec<u32> linear_mpf_seive(u32 n) {
  vec<u32> mpf(n);
  mpf[1] = 1;
  linear_seive(
      n,
      [&](u32 p) { mpf[p] = p; },
      [&](u32 i, u32 j) { mpf[i * j] = j; },
      [&](u32 i, u32 j) { mpf[i * j] = j; });
  return mpf;
}

}  // namespace tifa_libs::math

#endif