#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "../../code/geo2d/argsort.hpp"
#include "../../code/geo2d/point.hpp"

using point = tifa_libs::geo::point<tifa_libs::i64>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n;
  std::cin >> n;
  tifa_libs::vec<point> vp(n);
  for (auto& i : vp) std::cin >> i;
  tifa_libs::geo::argsort(vp);
  for (auto& i : vp) std::cout << i << '\n';
  return 0;
}
