#ifndef BENEVOLENCE_ACCUMULATOR
#define BENEVOLENCE_ACCUMULATOR

#include "constants.h"
#include <array>

using Accumulator = std::array<float, hidden_size * 2>;
/*class Accumulator {
public:
    std::array<float, HIDDEN> vals;

    Accumulator(std::array<float, HIDDEN> values) : vals(values) {}

    static Accumulator load_biases(const NetworkParams& nnue) {
        const auto& bias = nnue.vals[FEATURE_BIAS];
        Accumulator accumulator;
        std::copy_n(bias.begin(), HIDDEN, accumulator.vals.begin());
        return accumulator;
    }

    void add_feature(size_t feature_idx, const NetworkParams& nnue) {
        size_t start = feature_idx * HIDDEN;
        std::transform(nnue.vals.begin() + start, nnue.vals.begin() + start + HIDDEN, vals.begin(), vals.begin(), std::plus<float>());
    }
};*/

#endif