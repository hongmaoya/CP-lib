#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/conv/conv_mtt.hpp"
#include "../../code/math/mint_d63.hpp"
#include "../../code/util/ios_container.hpp"

using mint = tifa_libs::math::mint_d63<-1>;

int main() {
  mint::set_mod(1000000007);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<mint> a(n), b(m);
  std::cin >> a >> b;
  std::cout << tifa_libs::math::conv_mtt<mint, long double>(a, b) << '\n';
  return 0;
}
