#ifndef TIFALIBS_POLY_INT
#define TIFALIBS_POLY_INT

#include "poly.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_int(poly<T> const &p) {
  using mint = typename T::value_type;
  auto _ = p;
  for (usz i = _.size() - 1; i; --i) _[i] = _[i - 1] * mint(i).inv();
  _[0] = 0;
  return _;
}

}  // namespace tifa_libs::math

#endif