#ifndef TIFA_LIBS_GRAPH_KRUSKAL_RECONSTRUCTION_TREE
#define TIFA_LIBS_GRAPH_KRUSKAL_RECONSTRUCTION_TREE

#include "../ds/dsu_basic.hpp"
#include "../tree/tree.hpp"

namespace tifa_libs::graph {

namespace kruskal_re_tree_impl_ {

template <class T>
std::pair<tree, vec<T>> run_(tree& tr, vec<std::tuple<T, u32, u32>> const& sorted_a) {
  u32 n = u32((tr.g.size() + 1) / 2);
  vec<T> w_(2 * n - 1);
  ds::dsu_basic dsu(2 * n - 1);
  u32 m = n - 1, cnt = n;
  for (auto [w, u, v] : sorted_a) {
    u = (u32)dsu.find(u), v = (u32)dsu.find(v);
    if (u != v) {
      u32 t = cnt++;
      w_[t] = w;
      tr.add_arc(t, u), tr.add_arc(t, v);
      dsu.merge(t, u), dsu.merge(t, v);
      --m;
    }
    if (!m) break;
  }
  tr.root = cnt - 1;
  return {tr, w_};
}

}  // namespace kruskal_re_tree_impl_

//!! edge: w u v
//! MUST be sorted
template <class EW>
std::pair<tree, vec<EW>> kruskal_re_tree(vec<std::tuple<EW, u32, u32>> const& sorted_a, u32 n) {
  tree tr(2 * n - 1, 2 * n - 1);
  return kruskal_re_tree_impl_::run_(tr, sorted_a);
}

}  // namespace tifa_libs::graph

#endif