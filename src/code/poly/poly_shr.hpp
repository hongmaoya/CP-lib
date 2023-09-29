#ifndef TIFALIBS_POLY_SHR
#define TIFALIBS_POLY_SHR

#include "poly.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_shr(poly<T> const &p, size_t x) {
  if (!x) return p;
  auto _ = p;
  if (x >= _.size()) {
    std::fill(_.data().begin(), _.data().end(), 0);
    return _;
  }
  std::fill(_.data().begin(), std::move_backward(_.data().begin(), _.data().end() - x, _.data().end()), 0);
  return _;
}

}  // namespace tifa_libs::math

#endif