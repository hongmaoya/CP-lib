#ifndef TIFALIBS_CONV_CONV_NTT
#define TIFALIBS_CONV_CONV_NTT

#include "../util/util.hpp"
#include "ntt.hpp"

namespace tifa_libs::math {

template <class mint>
inline vec<mint> conv_ntt(vec<mint> l, vec<mint> r, usz ans_size) {
  static NTT<mint> ntt;
  ntt.bzr(std::max({l.size(), r.size(), std::min(l.size() + r.size() - 1, ans_size)}));
  ntt.dif(l);
  ntt.dif(r);
  for (usz i = 0; i < ntt.size(); ++i) l[i] *= r[i];
  ntt.dit(l);
  l.resize(ans_size);
  return l;
}
template <class mint>
inline vec<mint> conv_ntt(vec<mint> const &l, vec<mint> const &r) { return conv_ntt(l, r, l.size() + r.size() - 1); }

template <class mint, class T = u64>
inline vec<mint> conv_ntt(vec<T> const &l, vec<T> const &r, usz ans_size) {
  vec<mint> l_, r_;
  l_.reserve(l.size());
  r_.reserve(r.size());
  for (auto i : l) l_.push_back(i);
  for (auto i : r) r_.push_back(i);
  return conv_ntt(l_, r_, ans_size);
}
template <class mint, class T = u64>
inline vec<mint> conv_ntt(vec<T> const &l, vec<T> const &r) { return conv_ntt<mint, T>(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif