#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

#include "../../code/math/mint_d31.hpp"
#include "../../code/matrix/mat.hpp"
#include "../../code/matrix/mat_ge_basic.hpp"
#include "../../code/matrix/mat_inv.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mint::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](mint const &x) { return x.val() == 0; };
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_basic(m, is_0, f); };
  auto res = tifa_libs::math::mat_inv(a, is_0, ge);
  if (res)
    std::cout << res.value();
  else
    std::cout << "-1\n";
  return 0;
}
