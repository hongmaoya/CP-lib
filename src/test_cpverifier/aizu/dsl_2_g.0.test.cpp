#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_G"

#include "../../code/ds/segtree0.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n, q;
  std::cin >> n >> q;
  tifa_libs::vec<tifa_libs::i64> a(n);
  auto min = [](tifa_libs::i64 a, tifa_libs::i64 b) { return std::min(a, b); };
  auto max = [](tifa_libs::i64 a, tifa_libs::i64 b) { return std::max(a, b); };
  tifa_libs::ds::segtree0<tifa_libs::i64, decltype(min)> segt(a);
  for (size_t i = 1; i <= q; ++i) {
    size_t opt, l, r;
    std::cin >> opt >> l >> r;
    --l, --r;
    if (opt == 0) {
      tifa_libs::i64 x;
      std::cin >> x;
      segt.add(1, 0, n - 1, l, r, x);
    } else {
      std::cout << segt.querys(1, 0, n - 1, l, r) << '\n';
    }
  }
  return 0;
}