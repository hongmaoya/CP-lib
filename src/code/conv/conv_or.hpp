#ifndef TIFALIBS_CONV_CONV_OR
#define TIFALIBS_CONV_CONV_OR

#include "zmt_subset.hpp"

namespace tifa_libs::math {

template <class T>
inline vec<T> conv_or(vec<T> l, vec<T> r) {
  zt_subset(l);
  zt_subset(r);
  for (usz i = 0; i < l.size(); ++i) l[i] *= r[i];
  mt_subset(l);
  return l;
}

}  // namespace tifa_libs::math

#endif