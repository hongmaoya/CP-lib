#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"

#include "../../code/math/mat_det_rd.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/math/spmat.hpp"
#include "../../code/rand/gen.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using mat = tifa_libs::math::spmat<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 n, k;
  std::cin >> n >> k;
  mat a(n, n);
  for (tifa_libs::u64 i = 0, x, y, z; i < k; ++i) {
    std::cin >> x >> y >> z;
    a(x, y) = z;
  }
  auto is0 = [](mint const &x) { return x.val() == 0; };
  tifa_libs::rand::Gen gen(std::mt19937(), std::uniform_int_distribution<tifa_libs::u32>(1, mint::mod() - 1));
  std::cout << tifa_libs::math::det_rd(a, gen, is0) << '\n';
  return 0;
}