#ifndef TIFA_LIBS_MATH_PARTITION_GEN
#define TIFA_LIBS_MATH_PARTITION_GEN

#include "../poly/poly.hpp"
#include "../poly/poly_inv.hpp"

namespace tifa_libs::math {

// partition[i] = p(i), i=0,1,...,n
template <class T>
inline poly<T> partition_gen(u64 n) {
  poly<T> p(n + 1);
  p[0] = 1;
  for (u64 k = 1; k <= n; ++k) {
    u64 k1 = k * (3 * k + 1) / 2;
    u64 k2 = k * (3 * k - 1) / 2;
    if (k2 > n) break;
    if (k1 <= n) p[k1] += ((k & 1) ? -1 : 1);
    if (k2 <= n) p[k2] += ((k & 1) ? -1 : 1);
  }
  return poly_inv(p);
}

}  // namespace tifa_libs::math

#endif