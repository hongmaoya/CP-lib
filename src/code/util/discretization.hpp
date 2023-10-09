#ifndef TIFA_LIBS_UTIL_DISCRETIZATION
#define TIFA_LIBS_UTIL_DISCRETIZATION

#include "util.hpp"

namespace tifa_libs::util {

template <class T = vec<int>>
T discretization(T const &v) {
  T _ = v;
  std::sort(_.begin(), _.end());
  _.erase(std::unique(_.begin(), _.end()), _.end());
  for (auto &i : v) i = std::lower_bound(_.begin(), _.end(), i) - _.begin();
  return _;
}

}  // namespace tifa_libs::util

#endif