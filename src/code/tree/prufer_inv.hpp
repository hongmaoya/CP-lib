#ifndef TIFA_LIBS_TREE_PRUFER_INV
#define TIFA_LIBS_TREE_PRUFER_INV

#include "../util/util.hpp"

namespace tifa_libs::graph {

//! vertex ID starts at 1
//! tree root = n
// prüfer code of vertex i is code[i], code[0] = 0
inline vec<u32> prufer_inv(vec<u32> const& code) {
  u32 n = u32(code.size() + 1);
  vec<u32> deg(n + 1);
  for (u32 i = 1; i < n - 1; ++i) ++deg[code[i]];
  vec<u32> fa(n);
  for (u32 i = 1, j = 1; i < n; ++i, ++j) {
    while (deg[j]) ++j;
    fa[j] = code[i];
    while (i < n - 1 && !--deg[code[i]] && code[i] < j) fa[code[i]] = (i + 1 == n - 1 ? n : code[i + 1]), ++i;
  }
  return fa;
}

}  // namespace tifa_libs::graph

#endif