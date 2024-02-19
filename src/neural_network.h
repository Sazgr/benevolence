#include "accumulator.h"
#include "features.h"
#include "gradients.h"
#include "types.h"
#include <array>
#include <cmath>
#include <cstring>
#include <random>
#include <string>

struct Neural_network {
    std::array<float, input_size * hidden_size * input_buckets> input_features;  
    std::array<float, hidden_size> input_bias;
    std::array<float, hidden_size * 2 * output_buckets> hidden_features;
    std::array<float, output_size * output_buckets> hidden_bias;

    Neural_network() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<float> input_distribution(0.0, std::sqrt(1.0 / static_cast<float>(32)));
        std::normal_distribution<float> hidden_distribution(0.0, std::sqrt(1.0 / static_cast<float>(hidden_size)));
        for (int i = 0; i < input_size * hidden_size * input_buckets; ++i) {
            input_features[i] = input_distribution(gen);
        }
        for (int i = 0; i < hidden_size * 2 * output_buckets; ++i) {
            hidden_features[i] = hidden_distribution(gen);
        }
        std::memset(input_bias.data(), 0, sizeof(float) * hidden_size);
        std::memset(hidden_bias.data(), 0, sizeof(float) * output_size * output_buckets);
    }

    std::pair<float, int> forward(const Features& features, bool side_to_move, Accumulator& accumulator, Accumulator& activated) const;
    void back_propagate(const Features& features, bool side_to_move, Accumulator& accumulator, Accumulator& activated, u64 bucket, float err, Batch_gradients& gradient) const;
    void load(const std::string& path);
    void save(const std::string& path);
    void quantize(const std::string& path);
};
