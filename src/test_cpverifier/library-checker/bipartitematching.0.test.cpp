#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include "../../code/graph/dinic.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 l, r, m;
  std::cin >> l >> r >> m;
  u32 s = l + r, t = l + r + 1;
  tifa_libs::graph::dinic big(l + r + 2, s, t);
  for (u32 i = 0; i < l; ++i) big.add(s, i, 1);
  for (u32 i = 0; i < r; ++i) big.add(i + l, t, 1);
  for (u32 i = 0, u, v; i < m; ++i) std::cin >> u >> v, big.add(u, v + l, 1);
  std::cout << big() << '\n';
  for (u32 i = 0; i < l; ++i) {
    u32 ret = s;
    for (auto v : big.e[i])
      if (v.w == 0 && l <= v.to && v.to < l + r) {
        ret = v.to - l;
        break;
      }
    if(ret != s) std::cout << i << ' ' << ret << '\n';
  }
  return 0;
}
