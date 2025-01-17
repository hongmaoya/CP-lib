#ifndef TIFA_LIBS_GRAPH_RINGENUM3
#define TIFA_LIBS_GRAPH_RINGENUM3

#include "alist.hpp"

namespace tifa_libs::graph {

namespace ringenum3_impl_ {

template <class F>
inline void run(alist const& dg, F func) {
  u32 n = (u32)dg.g.size();
  vec<bool> vis(n);
  for (u32 u = 0; u < n; ++u) {
    for (u32 v : dg.g[u]) vis[v].flip();
    for (u32 v : dg.g[u])
      for (u32 w : dg.g[v])
        if (vis[w]) func(u, v, w);
    for (u32 v : dg.g[u]) vis[v].flip();
  }
}

}  // namespace ringenum3_impl_

//! should be simple undirected graph
// func(u, v, w) forall {u,v,w} is C3
template <class F>
inline void ringenum3(vec<u32> const& deg, vec<ptt<u32>> const& edges, F func) {
  alist dg(deg.size());
  for (auto [u, v] : edges) {
    if (deg[u] < deg[v] || (deg[u] == deg[v] && u > v)) std::swap(u, v);
    dg.add_arc(u, v);
  }
  ringenum3_impl_::run(dg, func);
}
//! vertex ID: 0..n-1
//! should be simple undirected graph
// func(u, v, w) forall {u,v,w} is C3
template <class F>
inline void ringenum3(u32 n, vec<ptt<u32>> const& edges, F func) {
  vec<u32> deg(n);
  for (auto [u, v] : edges) ++deg[u], ++deg[v];
  ringenum3(deg, edges, func);
}
inline u64 ringcnt3(u32 n, vec<ptt<u32>> const& edges) {
  u64 ans = 0;
  ringenum3(n, edges, [&](u32, u32, u32) { ++ans; });
  return ans;
}

}  // namespace tifa_libs::graph

#endif