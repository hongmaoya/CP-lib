#ifndef TIFALIBS_CONV_CONV_CZT
#define TIFALIBS_CONV_CONV_CZT

#include "../bit/bceil.hpp"
#include "../math/proot_u64.hpp"
#include "../poly/poly_czt.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> conv_czt(poly<T> l, poly<T> r, usz ans_size) {
  using mint = typename T::value_type;
  constexpr u64 m = T::value_type::mod();
  u64 s = bit::bceil(l.size() + r.size() - 1);
  assert((m - 1) % s == 0);
  mint c = qpow(mint(proot_u64(m)), (m - 1) / s);
  l.resize(s);
  r.resize(s);
  l = poly_czt(l, c);
  r = poly_czt(r, c);
  for (usz i = 0; i < s; ++i) l[i] *= r[i];
  l = poly_czt(l, c.inv());
  l.resize(ans_size);
  return l *= mint(s).inv();
}
template <class T>
inline poly<T> conv_czt(poly<T> const &l, poly<T> const &r) { return conv_czt(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif