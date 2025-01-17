#ifndef TIFA_LIBS_MATH_GEN_IFACT
#define TIFA_LIBS_MATH_GEN_IFACT

#include "../math/mul_mod_u.hpp"
#include "gen_inv.hpp"

namespace tifa_libs::math {

// (i!)^{-1} from i=0..n-1
inline vec<u64> gen_ifact(u32 n, u64 mod, vec<u64> inv) {
  for (u32 i = 2; i < n; ++i) inv[i] = mul_mod_u(inv[i], inv[i - 1], mod);
  return inv;
}
// (i!)^{-1} from i=0..n-1
inline vec<u64> gen_ifact(u32 n, u64 mod) { return gen_ifact(n, mod, gen_inv(n, mod)); }
// (i!)^{-1} from i=0..n-1
template <class mint>
inline vec<mint> gen_ifact(u32 n, vec<mint> inv) {
  for (u32 i = 2; i < n; ++i) inv[i] *= inv[i - 1];
  return inv;
}
// (i!)^{-1} from i=0..n-1
template <class mint>
inline vec<mint> gen_ifact(u32 n) { return gen_ifact(n, gen_inv<mint>(n)); }

}  // namespace tifa_libs::math

#endif