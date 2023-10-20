#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_quotients"

#include "../../code/math/do_quot.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 n;
  std::cin >> n;
  tifa_libs::vec<tifa_libs::u64> ans;
  tifa_libs::math::do_quot(n, [&ans](tifa_libs::u64, tifa_libs::u64, tifa_libs::u64 q) { ans.push_back(q); });
  std::sort(ans.begin(), ans.end());
  std::cout << ans.size() << '\n';
  for (size_t i = 0; i < ans.size(); ++i) std::cout << ans[i] << " \n"[i + 1 == ans.size()];
  return 0;
}
