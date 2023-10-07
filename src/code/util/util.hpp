#ifndef TIFA_LIBS_UTIL_UTIL
#define TIFA_LIBS_UTIL_UTIL

#include <bits/stdc++.h>

namespace tifa_libs {

using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;

template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using vvvec = vec<vvec<T>>;
template <class T>
using pq = std::priority_queue<T>;
template <class T>
using pqg = std::priority_queue<T, vec<T>, std::greater<T>>;

template <class U, class T>
using vvp = vvec<std::pair<U, T>>;

template <class T>
using ptt = std::pair<T, T>;
template <class T>
using pt4 = std::tuple<T, T, T, T>;

}  // namespace tifa_libs

#endif