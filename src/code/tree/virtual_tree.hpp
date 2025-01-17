#ifndef TIFA_LIBS_TREE_VIRTUAL_TREE
#define TIFA_LIBS_TREE_VIRTUAL_TREE

#include "lca_hld.hpp"
#include "tree.hpp"

namespace tifa_libs::graph {

class virtual_tree {
  tree& tr;
  lca_hld lca_;
  vec<u32> st;

  void insert(u32 x) {
    u32 lca = lca_(x, st.back());
    if (lca == st.back()) {
      st.push_back(x);
      return;
    }
    while (st.size() > 1 && lca_.info.dep[st[st.size() - 2]] >= lca_.info.dep[lca]) vt.add_arc(st[st.size() - 2], st.back()), st.pop_back();
    if (lca_.info.dep[st.back()] > lca_.info.dep[lca]) vt.add_arc(lca, st.back()), st.pop_back();
    if (st.back() != lca) st.push_back(lca);
    st.push_back(x);
  }

 public:
  tree vt;

  virtual_tree(tree& tr) : tr(tr), lca_(tr), vt(tr.g.size()) {}

  void build(vec<u32>& a) {
    std::sort(a.begin(), a.end(), [&](u32 a, u32 b) { return lca_.info.dfn[a] < lca_.info.dfn[b]; });
    vt.g.clear();
    st.push_back(tr.root);
    for (u32 x : a) insert(x);
    while (st.size() > 1) vt.add_arc(st[st.size() - 2], st.back()), st.pop_back();
    st.pop_back();
  }
};

}  // namespace tifa_libs::graph

#endif