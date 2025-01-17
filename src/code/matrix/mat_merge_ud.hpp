#ifndef TIFA_LIBS_MATH_MAT_MERGE_UD
#define TIFA_LIBS_MATH_MAT_MERGE_UD

#include "mat.hpp"

namespace tifa_libs::math {

// [u] [d] -> [u; d]
template <class T>
inline matrix<T> mat_merge_ud(const matrix<T> &u, const matrix<T> &d) {
  usz c_ = u.col();
  assert(c_ == d.col());
  usz ur_ = u.row(), dr_ = d.row(), r_ = ur_ + dr_;
  matrix<T> ret(r_, c_);
  ret.apply_range(0, ur_, 0, c_, [&u](usz i, usz j, T &val) { val = u(i, j); });
  ret.apply_range(ur_, r_, 0, c_, [ur_, &d](usz i, usz j, T &val) { val = d(i - ur_, j); });
  return ret;
}

}  // namespace tifa_libs::math

#endif