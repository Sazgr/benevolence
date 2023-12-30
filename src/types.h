#ifndef BENEVOLENCE_TYPES
#define BENEVOLENCE_TYPES

#include <cstdint>

using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u16 = std::uint16_t;
using u8 = std::uint8_t;
using i64 = std::int64_t;
using i32 = std::int32_t;
using i16 = std::int16_t;
using i8 = std::int8_t;

inline int popcount(u64 bits) {return __builtin_popcountll(bits);}
inline int get_lsb(u64 bits) {return __builtin_ctzll(bits);}
inline int get_msb(u64 bits) {return __builtin_clzll(bits) ^ 63;}
inline int pop_lsb(u64& bits) {
    int lsb = get_lsb(bits);
    bits &= bits - 1;
    return lsb;
}

#endif
