#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include "../../code/ds/dsu_pd.hpp"

constexpr size_t Q = 200005;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, q;
  std::cin >> n >> q;
  tifa_libs::vvec<tifa_libs::pt3<tifa_libs::u32>> tr(Q), qry(Q);
  std::bitset<Q> ans;
  tifa_libs::u32 cnt = 0;
  for (size_t i = 1; i <= q; ++i) {
    tifa_libs::u32 t, u, v;
    tifa_libs::i32 k;
    std::cin >> t >> k >> u >> v;
    ++k;
    if (t == 0)
      tr[(tifa_libs::u32)k].emplace_back(i, u, v);
    else
      qry[(tifa_libs::u32)k].emplace_back(cnt++, u, v);
  }
  tifa_libs::ds::dsu_pd dsu(n + 1);
  auto dfs = [&](auto&& dfs, tifa_libs::u32 v) -> void {
    for (auto [i, x, y] : qry[v]) ans[i] = dsu.same(x, y);
    for (auto [_, x, y] : tr[v]) {
      auto t = dsu.time();
      dsu.merge(x, y);
      dfs(dfs, _);
      dsu.rollback(t);
    }
  };
  dfs(dfs, 0);
  for (size_t i = 0; i < cnt; ++i) std::cout << ans[i] << '\n';
  return 0;
}
