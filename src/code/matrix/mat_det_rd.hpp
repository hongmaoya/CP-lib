#ifndef TIFA_LIBS_MATH_MAT_DET
#define TIFA_LIBS_MATH_MAT_DET

#include "lfsr_bm.hpp"

namespace tifa_libs::math {

template <class Mat, class Gn, class Is0, class T = typename Mat::value_type>
T det_rd(Mat mat, Gn &gen, Is0 is0) {
  usz n = mat.row();
  assert(n == mat.col());
  auto gen2 = [&gen](usz n) {
    vec<T> v(n);
    std::generate(v.begin(), v.end(), gen);
    return v;
  };
  std::vector<T> u = gen2(n), v = gen2(n), diag = gen2(n), _(n * 2);
  for (usz i = 0; i < n * 2; ++i) {
    _[i] = std::transform_reduce(u.begin(), u.end(), v.begin(), T{});
    for (usz i = 0; i < n; ++i) v[i] *= diag[i];
    v = mat.lproj(v);
  }
  std::vector<T> mp = lfsr_bm(_, is0);
  T res = mp.back() / std::accumulate(diag.begin(), diag.end(), T(1), std::multiplies<T>());
  return (n & 1) == 1 ? -res : res;
}

}  // namespace tifa_libs::math

#endif