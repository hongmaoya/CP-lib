#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include "../../code/ds/lichao_segtree.hpp"
#include "../../code/util/discretization.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n, q;
  std::cin >> n >> q;
  vec<i64> lsh;
  struct seg {
    i64 a, b, l, r;
  };
  vec<seg> se(n);
  struct que {
    usz opt;
    i64 pos;
    seg k;
  };
  vec<que> qu(q);
  for (usz i = 0; i < n; ++i)
    std::cin >> se[i].l >> se[i].r >> se[i].a >> se[i].b, se[i].r -= 1, lsh.push_back(se[i].l), lsh.push_back(se[i].r);
  for (usz i = 0; i < q; ++i) {
    std::cin >> qu[i].opt;
    if (qu[i].opt)
      std::cin >> qu[i].pos, lsh.push_back(qu[i].pos);
    else
      std::cin >> qu[i].k.l >> qu[i].k.r >> qu[i].k.a >> qu[i].k.b, qu[i].k.r -= 1, lsh.push_back(qu[i].k.l), lsh.push_back(qu[i].k.r);
  }
  lsh = tifa_libs::uniq<vec<i64>>(lsh);
  auto _min = [](i64 a, i64 b) { return std::min(a, b); };
  tifa_libs::ds::lichao_segtree<i64, decltype(_min)> tr(lsh, _min);
  for (usz i = 0; i < n; ++i)
    tr.add(se[i].a, se[i].b, se[i].l, se[i].r);
  for (usz i = 0; i < q; ++i)
    if (qu[i].opt) {
      i64 ret = tr.query(qu[i].pos);
      if (ret == INT64_MAX) std::cout << "INFINITY\n";
      else std::cout << ret << '\n';
    } else
      tr.add(qu[i].k.a, qu[i].k.b, qu[i].k.l, qu[i].k.r);
  return 0;
}
