#ifndef BENEVOLENCE_GRADIENTS
#define BENEVOLENCE_GRADIENTS

#include "constants.h"
#include <array>
#include <cstring>

struct Gradient {
    float m = 0;
    float v = 0;

    void clear() {
        m = 0;
        v = 0;
    }
};

template <typename T>
class Net_gradients {
public:
    std::array<T, input_size * hidden_size> input_features;
    std::array<T, hidden_size> input_bias;
    std::array<T, hidden_size * 2> hidden_features;
    std::array<T, output_size> hidden_bias;

    Net_gradients() {
        clear();
    }

    void clear() {
        std::memset(input_features.data(), 0, sizeof(T) * input_size * hidden_size);
        std::memset(input_bias.data(), 0, sizeof(T) * hidden_size);
        std::memset(hidden_features.data(), 0, sizeof(T) * hidden_size * 2);
        std::memset(hidden_bias.data(), 0, sizeof(T) * output_size);
    }
};

using Adam_gradients = Net_gradients<Gradient>;
using Batch_gradients = Net_gradients<float>;

#endif