#ifndef TIFALIBS_POLY_POLYDATA_D3NTT
#define TIFALIBS_POLY_POLYDATA_D3NTT

#include "../conv/conv_3ntt.hpp"
#include "../conv/conv_naive.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint, class mint0, class mint1, class mint2>
struct polydata_d3ntt {
  using value_type = mint;

  vec<mint> d;

  explicit constexpr polydata_d3ntt(usz sz = 1, value_type const &val = value_type{}) : d(sz, val) {}
  constexpr polydata_d3ntt(typename vec<mint>::const_iterator begin, typename vec<mint>::const_iterator end) : d(begin, end) {}
  explicit constexpr polydata_d3ntt(std::initializer_list<mint> v) : d(v) {}
  explicit constexpr polydata_d3ntt(vec<mint> const &v) : d(v) {}

  void conv(polydata_d3ntt const &r, usz ans_size) { d = ans_size < 32 ? conv_naive(d, r.d, ans_size) : conv_3ntt<mint, mint0, mint1, mint2>(d, r.d, ans_size); }
  void conv(polydata_d3ntt const &r) { conv(r, d.size() + r.d.size() - 1); }
};

}  // namespace tifa_libs::math

#endif