#ifndef TIFA_LIBS_DS_DSU_BASIC
#define TIFA_LIBS_DS_DSU_BASIC

#include "../util/util.hpp"

namespace tifa_libs::ds {

class dsu_basic {
  vec<size_t> fa;

 public:
  explicit dsu_basic(size_t sz) : fa(sz) { std::iota(fa.begin(), fa.end(), 0); }

  size_t find(size_t x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
  bool in_same_group(size_t x, size_t y) { return find(x) == find(y); }
  void merge(size_t x, size_t y) { fa[find(x)] = find(y); }
};

}  // namespace tifa_libs::ds

#endif