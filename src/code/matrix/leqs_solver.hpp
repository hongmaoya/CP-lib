#ifndef TIFA_LIBS_MATH_LEQS_SOLVER
#define TIFA_LIBS_MATH_LEQS_SOLVER

#include "../util/abs_constexpr.hpp"
#include "mat.hpp"
#include "mat_merge_lr.hpp"
#include "mat_trans.hpp"

namespace tifa_libs::math {

template <class T, class Is0, class Ge>
inline std::optional<matrix<T>> leqs_solver(matrix<T> const &A, matrix<T> const &b, Is0 is0, Ge ge) {
  usz r_ = A.row(), c_ = A.col();
  assert(b.col() == 1 && r_ == b.row());
  matrix<T> Ab = mat_merge_lr(A, b);
  u64 rk = (u64)abs(ge(Ab, false));
  if (rk > c_) return {};
  if (!is0(Ab(rk - 1, c_))) {
    bool f = true;
    for (usz i = 0; i < c_; ++i)
      if (!is0(Ab(rk - 1, i))) {
        f = false;
        break;
      }
    if (f) return {};
  }
  for (usz i = rk; i < r_; ++i)
    if (!is0(Ab(i, c_))) return {};
  vec<bool> used(c_, false);
  vec<usz> idxs;
  for (usz i = 0, _ = 0; i < r_; ++i) {
    while (i + _ < c_ && is0(Ab(i, i + _))) ++_;
    if (i + _ >= c_) break;
    used[i + _] = true;
    idxs.push_back(i + _);
  }
  matrix<T> sol(c_ - rk + 1, c_);
  {
    auto &v = sol.data()[0];
    for (usz y = rk - 1; ~y; --y) {
      usz f = idxs[y];
      v[f] = Ab(y, c_);
      for (usz x = f + 1; x < c_; x++) v[f] -= Ab(y, x) * v[x];
      v[f] /= Ab(y, f);
    }
  }
  for (usz s = 0, _ = 0; s < c_; ++s) {
    if (used[s]) continue;
    auto &v = sol.data()[++_];
    v[s] = 1;
    for (usz y = rk - 1; ~y; --y) {
      usz f = idxs[y];
      for (usz x = f + 1; x < c_; x++) v[f] -= Ab(y, x) * v[x];
      v[f] /= Ab(y, f);
    }
  }
  return transpose(sol);
}

}  // namespace tifa_libs::math

#endif