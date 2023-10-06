#ifndef TIFA_LIBS_DS_ST_ARRAY
#define TIFA_LIBS_DS_ST_ARRAY

#include "../bit/log2.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, class F>
class st_array {
  vvec<T> st;
  F f;

 public:
  st_array(vec<T> const &a, F func) : st((size_t)bit::log2(a.size()) + 1, vec<T>(a.size())), f(func) {
    size_t n = a.size();
    st[0] = a;
    for (size_t j = 1, m = (size_t)bit::log2(n) + 1; j < m; ++j)
      for (size_t i = 0; i < n; ++i) st[j][i] = f(st[j - 1][i], st[j - 1][std::min(n - 1, i + (1 << (j - 1)))]);
  }
  T query(size_t l, size_t r) const {
    size_t k = (size_t)bit::log2(1 + r - l);
    return f(st[k][l], st[k][r - (1 << k) + 1]);
  }
};

}  // namespace tifa_libs::ds

#endif