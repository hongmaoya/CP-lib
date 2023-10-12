#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../../code/comb/lucas.hpp"
#include "../../code/comb/mcn_mod.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 t, m;
  std::cin >> t >> m;
  if (m < 1e7) {
    tifa_libs::math::Lucas mCn(m);
    while (t--) {
      tifa_libs::i64 n, k;
      std::cin >> n >> k;
      std::cout << mCn(n, k) << '\n';
    }
  } else {
    tifa_libs::math::Binom mCn(m, 10'000'001);
    while (t--) {
      tifa_libs::i64 n, k;
      std::cin >> n >> k;
      std::cout << mCn.mCn(n, k) << '\n';
    }
  }
  return 0;
}
