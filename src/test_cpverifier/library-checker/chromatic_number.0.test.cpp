#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"

#include "../../code/graph/chrom_num.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v), g.add_arc(v, u);
  }
  std::cout << tifa_libs::graph::chrom_num(g) << '\n';
  return 0;
}
