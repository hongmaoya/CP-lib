#ifndef TIFA_LIBS_STR_SUFFIX_AUTOMATON
#define TIFA_LIBS_STR_SUFFIX_AUTOMATON

#include "../util/util.hpp"

namespace tifa_libs::str {
template <u32 SZ = 26>
class suffix_automaton {
  // super root is 0
  u32 last;
  struct YYZ {
    u32 len, link;
    std::array<u32, SZ> nex{};
    u64 sz;         // application 1
    u32 times;      // application 2
    bool is_clone;  // application 3
    u32 firstpos;   // application 3
  };

 public:
  u32 sz;
  vec<YYZ> st;
  suffix_automaton() : last(0), sz(1), st(1) { st[0].len = 0, st[0].link = -1u; }
  void extend(u32 c) {
    u32 cur = sz++;
    st.push_back(YYZ());
    st[cur].len = st[last].len + 1;
    st[cur].times = 1;                   // application 2
    st[cur].firstpos = st[cur].len - 1;  // application 3
    u32 p = last;

    while (p != -1u && !st[p].nex[c]) st[p].nex[c] = cur, p = st[p].link;
    if (p == -1u) st[cur].link = 0;
    else {
      u32 q = st[p].nex[c];
      if (st[p].len + 1 == st[q].len) st[cur].link = q;
      else {
        u32 clone = sz++;
        st.push_back(YYZ());
        st[clone].nex = st[q].nex;
        st[clone].len = st[p].len + 1;
        st[clone].link = st[q].link;
        st[clone].firstpos = st[q].firstpos;  // application 3
        st[clone].is_clone = 1;               // application 3

        while (p != -1u && st[p].nex[c] == q) st[p].nex[c] = clone, p = st[p].link;
        st[q].link = st[cur].link = clone;
      }
    }
    last = cur;
  }
  vvec<u32> e;
  void build() {
    e = vvec<u32>(sz);
    auto add = [&](u32 u, u32 v) { e[u].push_back(v); };
    for (u32 i = 1; i < sz; ++i) add(u32(st[i].link), i);
  }

  //!!! default: each character of t is lowercase English letters.
  std::pair<u32, bool> search(std::string t) {  // application 0
    u32 u = 0, i = 0, base = u32('a');
    while (i < t.size()) {
      if (!st[u].nex[u32(t[i]) - base]) return {i, false};
      u = st[u].nex[u32(t[i]) - base], ++i;
    }
    return {u32(u), true};
  }

  void getsz(u32 u = 0) {  // application 1
    st[u].sz = 1;
    for (auto v : st[u].nex)
      if (v) {
        if (!st[v].sz) getsz(v);
        st[u].sz += st[v].sz;
      }
  }

  //!!!   need build()
  void gettimes(u32 u = 0) {  // application 2
    for (auto v : e[u]) gettimes(v), st[u].times += st[v].times;
  }

  //!!!   need build(), search()
  void output_all_occurrences(u32 u, u32 P_length, vec<u32> &ans) {  // application 3
    if (!st[u].is_clone) ans.push_back(st[u].first_pos - P_length + 1);
    for (u32 v : e[u]) output_all_occurrences(v, P_length, ans);
  }

  //!!! default: each character of t is lowercase English letters.
  ptt<u32> lcs(std::string_view t) {  // application 4
    u32 v = 0, len = 0, ret = 0, end = 0, base = u32('a');
    for (u32 i = 0; i < t.size(); ++i) {
      while (v && !st[v].nex[u32(t[i]) - base]) v = st[v].link, len = st[v].len;
      if (st[v].nex[u32(t[i]) - base]) v = st[v].nex[u32(t[i]) - base], ++len;
      if (len > ret) ret = len, end = i;
    }
    return {end - ret + 1, ret};
  }
};

}  // namespace tifa_libs::str

#endif