#ifndef TIFA_LIBS_STR_HASH_SUBSTR_1MOD
#define TIFA_LIBS_STR_HASH_SUBSTR_1MOD

#include "../util/util.hpp"

namespace tifa_libs::str {

class hash_substr {
  protected:
    constexpr static u64 mod = (1ull << 61) - 1;
    constexpr static u64 _2e30n1 = (1ul << 30) - 1, _2e31n1 = (1ul << 31) - 1;
    constexpr static u64 mul_(u64 a, u64 b) {
        u64 au = a >> 31, ad = a & _2e31n1;
        u64 bu = b >> 31, bd = b & _2e31n1;
        u64 _ = ad * bu + au * bd;
        return ((au * bu) << 1) + ad * bd + ((_ & _2e30n1) << 31) + (_ >> 30);
    }
    constexpr static u64 mod_(u64 a) {
        a = (a & mod) + (a >> 61);
        return a > mod ? a - mod : a;
    }

    bool reseted_;
    u32 b;
    vec<u64> p, hash;

  public:
    explicit hash_substr(u32 base): reseted_(false), b(0), p(), hash() { set_base(base); }
    void set_base(u32 base) {
        assert(base > 128);
        if (b == base) return;
        b = base;
        reseted_ = true;
    }
    void set(std::string_view s) {
        hash.resize(1, 0);
        hash.reserve(s.size() + 1);
        for (char c : s) hash.push_back(mod_(mul_(hash.back(), b) + (u64)c + 1));
        if (reseted_) {
            p.resize(1, 1);
            p.reserve(s.size() + 1);
            for (size_t i = 0; i < s.size(); ++i) p.push_back(mod_(mul_(p.back(), b)));
            reseted_ = false;
        }
    }
    constexpr u32 base() const { return b; }
    u64 get(size_t pos, size_t len = SIZE_MAX) const {
        assert(pos < hash.size());
        auto end_ = hash[pos + std::min(len, hash.size() - 1 - pos)];
        return mod_(end_ + mod * 7 - mul_(hash[pos], p[len]));
    }
};

}  // namespace tifa_libs::str

#endif