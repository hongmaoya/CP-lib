#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_4_A"

#include "../../code/geo2d/cvh.hpp"

using cvh = tifa_libs::geo2d::cvh<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(0);
  tifa_libs::u32 n;
  std::cin >> n;
  cvh p(n);
  std::cin >> p;
  p.init_nonstrict();
  std::cout << p.vs.size() << '\n';
  size_t now = 0;
  for (size_t i = 1; i < p.vs.size(); ++i)
    if (tifa_libs::geo2d::is_le(p[i].y, p[now].y) || (tifa_libs::geo2d::is_eq(p[i].y, p[now].y) && tifa_libs::geo2d::is_le(p[i].x, p[now].x))) now = i;
  for (size_t i = now; i < p.vs.size(); ++i) std::cout << p[i] << '\n';
  if (now)
    for (size_t i = 0; i < now; ++i) std::cout << p[i] << '\n';
  return 0;
}
