#ifndef TIFA_LIBS_MATH_CANTOR
#define TIFA_LIBS_MATH_CANTOR

#include "../ds/fenwick.hpp"

namespace tifa_libs::math {

//! [0, n)
//! p \in [1, n], a_i == a_j \iff i == j
inline vec<u32> cantor_seq(vec<u32> const &p) {
  usz n = p.size();
  ds::fenwick<u32> tr(n + 1);
  vec<u32> s(n);
  for (usz i = n - 1; ~i; --i) {
    s[i] = tr.sum(p[i]);
    tr.add(p[i], 1);
  }
  return s;
}

}  // namespace tifa_libs::math

#endif