#ifndef TIFA_LIBS_GRAPH_ALIST
#define TIFA_LIBS_GRAPH_ALIST

#include "../util/util.hpp"

namespace tifa_libs::graph {

struct alist {
  using value_type = vvec<u32>;
  value_type g;

  //! vertex ID: [0, n)
  explicit alist(usz n = 0) : g(n) {}

  void add_arc(u32 u, u32 v) { g[u].push_back(v); }
};

}  // namespace tifa_libs::graph

#endif