#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

#include "../../code/math/mint_ds.hpp"
#include "../../code/matrix/mat_charpoly.hpp"
#include "../../code/util/ios_container.hpp"

using mint = tifa_libs::math::mint_ds<-1>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mint::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;
  if (n == 0) {
    std::cout << "1\n";
    return 0;
  }
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](mint const &x) { return x.val() == 0; };
  std::cout << tifa_libs::math::charpoly(a, is_0) << '\n';
  return 0;
}
