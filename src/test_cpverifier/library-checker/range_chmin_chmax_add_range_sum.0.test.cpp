#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"

#include "../../code/ds/segtree_beats.hpp"


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n, q;
  std::cin >> n >> q;
  vec<i64> a(n);
  for(auto& x: a) std::cin >> x;
  tifa_libs::ds::segtree_beats<i64> seg(a);
  for(usz i = 0, opt, l, r; i < q; ++ i) {
    std::cin >> opt >> l >> r;
    -- r;
    if(opt == 3) std::cout << seg.querys(1, 0, n - 1, l, r)<< '\n';
    else {
      i64 b;
      std::cin >> b;
      if(opt == 0) seg.chmin(1, 0, n - 1, l, r, b);
      else if(opt == 1) seg.chmax(1, 0, n - 1, l, r, b);
      else seg.add(1, 0, n - 1, l, r, b);
    }
  }
  return 0;
}
