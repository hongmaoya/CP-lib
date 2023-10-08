#ifndef TIFA_LIBS_DS_ST_ARRAY_2D
#define TIFA_LIBS_DS_ST_ARRAY_2D

#include "../bit/log2.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, T (*op)(T, T)>
class st_array_2d {
  vvvec<T> st;

 public:
  st_array_2d(vvec<T> const &a) : st((size_t)bit::log2(std::max(a.size(), a[0].size())) + 1, vvec<T>(a.size(), vec<T>(a[0].size()))) {
    size_t n = a.size(), n2 = a[0].size();
    st[0] = a;
    for (size_t j = 1, m = (size_t)bit::log2(std::max(n, n2)) + 1; j < m; ++j)
      for (size_t i = 0, i_; i < n; ++i) {
        i_ = std::min(n - 1, i + (1 << (j - 1)));
        for (size_t k = 0, k_; k < n2; ++k) {
          k_ = std::min(n2 - 1, k + (1 << (j - 1)));
          st[j][i][k] = op(op(st[j - 1][i][k], st[j - 1][i_][k]), op(st[j - 1][i][k_], st[j - 1][i_][k_]));
        }
      }
  }
  //! [x, x + l] * [y, y + l]
  T query(size_t x, size_t y, size_t l) const {
    size_t k = (size_t)bit::log2(l + 1), ofs = (1 << k) - 1;
    return op(op(st[k][x][y], st[k][x + l - ofs][y]), op(st[k][x][y + l - ofs], st[k][x + l - ofs][y + l - ofs]));
  }
};

}  // namespace tifa_libs::ds

#endif