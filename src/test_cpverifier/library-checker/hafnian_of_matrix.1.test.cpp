#define PROBLEM "https://judge.yosupo.jp/problem/hafnian_of_matrix"

#include "../../code/math/mat_hafnian.hpp"
#include "../../code/math/mint_s63.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  std::cout << tifa_libs::math::hafnian(a);
  return 0;
}