#ifndef TIFA_LIBS_MATH_STIRLING1_COL_GEN
#define TIFA_LIBS_MATH_STIRLING1_COL_GEN

#include "../math/inverse.hpp"
#include "../poly/poly.hpp"
#include "../poly/poly_ln.hpp"
#include "../poly/poly_pow.hpp"
#include "fact_mod_gen.hpp"

namespace tifa_libs::math {

// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class T>
inline poly<T> stirling1_col_gen(u64 n, u64 k, vec<u64> const& fact) {
  if (k > n) return poly<T>(n + 1);
  u64 mod = T::value_type::mod();
  poly<T> f(n + 1);
  f[0] = f[1] = 1;
  f = poly_pow(poly_ln(f), k) * inverse(fact[k], mod);
  for (size_t i = 0; i <= n; ++i) f[i] *= ((i - k) & 1 ? mod - fact[i] : fact[i]);
  return f;
}
// stirling1[i] = {i \\brack k}, i=0,1,...,n
template <class T>
inline poly<T> stirling1_col_gen(u64 n, u64 k) { return stirling1_col_gen<T>(n, k, fact_mod_gen(n + 1, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif