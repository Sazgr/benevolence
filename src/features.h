#ifndef BENEVOLENCE_FEATURES
#define BENEVOLENCE_FEATURES

#include "types.h"
#include <array>

struct Features {
    std::array<std::array<i16, 2>, 32> features;
    u8 n = 0;
    u8 stm;
    inline void add(int16_t feature_black, int16_t feature_white) {
        features[n][0] = feature_black;
        features[n][1] = feature_white;
        ++n;
    }
    inline void clear() {
        stm = 0;
        n = 0;
    }
    std::array<i16, 2>& operator[](int index) {
        return features[index];
    }
};

const int king_buckets[64] {
    0, 0, 1, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 0, 0,
    2, 2, 3, 3, 3, 3, 2, 2,
    2, 2, 3, 3, 3, 3, 2, 2,
    2, 2, 3, 3, 3, 3, 2, 2,
    2, 2, 3, 3, 3, 3, 2, 2,
};

static inline int king_bucket(int king_square, bool king_color) {
    if constexpr (buckets > 1) {
        king_square = (56 * king_color) ^ king_square;
        return king_buckets[king_square];
    } else {
        return 0;
    }
}

static inline int index(int piece, int square, bool view, int king_square) {
    const int piece_color = !(piece & 1);
    const int piece_type = piece >> 1;
    square ^= (7 * !!(king_square & 0x4));
    return square + (piece_type) * 64 + !(piece_color ^ view) * 64 * 6 + king_bucket(king_square, view) * 64 * 12;
}

#endif