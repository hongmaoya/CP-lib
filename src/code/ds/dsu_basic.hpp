#ifndef TIFA_LIBS_DS_DSU_BASIC
#define TIFA_LIBS_DS_DSU_BASIC

#include "../util/util.hpp"

namespace tifa_libs::ds {
template <bool RANK_ = false>
class dsu_basic {
  vec<i32> p;

 public:
  explicit dsu_basic(usz sz) : p(sz, -1) {}

  i32 find(u32 x) { return p[x] < 0 ? (i32)x : p[x] = find((u32)p[x]); }
  u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }
  bool same(u32 x, u32 y) { return find(x) == find(y); }
  bool merge(u32 x, u32 y) {
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if constexpr (RANK_)
      if (p[x] > p[y]) std::swap(x, y);
    p[x] += p[y];
    p[y] = (i32)x;
    return true;
  }
};

}  // namespace tifa_libs::ds

#endif