#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_B"
#define ERROR 0.000001

#include "../../code/geo2d/tcenter_i.hpp"
#include "../../code/geo2d/triangle.hpp"

using tri = tifa_libs::geo::triangle<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(12);
  tri t;
  std::cin >> t;
  std::cout << tifa_libs::geo::center_I(t) << ' ' << tifa_libs::geo::radius_I(t) << '\n';
  return 0;
}
