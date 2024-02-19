#include "neural_network.h"
#include "types.h"
#include "dataloader.h"
#include <memory>
#include <fstream>
#include <iostream>

std::pair<float, int> Neural_network::forward(const Features& features, bool side_to_move, Accumulator& accumulator, Accumulator& activated) const {
    u64 bucket = 0; //output bucket
    float eval = hidden_bias[bucket];
    float* my_accumulator = accumulator.data();
    float* opp_accumulator = accumulator.data() + hidden_size;
    std::memcpy(my_accumulator, input_bias.data(), sizeof(float) * hidden_size);
    std::memcpy(opp_accumulator, input_bias.data(), sizeof(float) * hidden_size);
    for (int i = 0; i < features.count; ++i) {
        for (int j = 0; j < hidden_size; ++j) {
            my_accumulator[j] += input_features[features.features[i][side_to_move] * hidden_size + j];
            opp_accumulator[j] += input_features[features.features[i][!side_to_move] * hidden_size + j];
        }
    }
    for (int i = 0; i < 2 * hidden_size; ++i) {
        activated[i] = activation(accumulator[i]);
    }
    const float* hidden_features_bucket = hidden_features.data() + 2 * hidden_size * bucket;
    for (int i = 0; i < 2 * hidden_size; ++i) {
        eval += hidden_features_bucket[i] * activated[i];
    }
    return {eval, bucket};
}

void Neural_network::back_propagate(const Features& features, bool side_to_move, Accumulator& accumulator, Accumulator& activated, u64 bucket, float err, Batch_gradients& gradient) const {
    //hidden bias
    gradient.hidden_bias[bucket] += err;
    //hidden features
    float* hidden_features_bucket = gradient.hidden_features.data() + 2 * hidden_size * bucket;
    for (int i = 0; i < 2 * hidden_size; ++i) {
        hidden_features_bucket[i] += err * activated[i];
    }
    std::array<float, hidden_size * 2> components;
    for (int i = 0; i < hidden_size * 2; ++i) {
        components[i] = err * hidden_features_bucket[i] * activation.prime(accumulator[i]); //hiddenlosses
    }
    //input bias
    for (int i = 0; i < hidden_size; ++i) {
        gradient.input_bias[i] += components[i] + components[hidden_size + i];
    }
    //input features
    for (int i = 0; i < features.count; ++i) {
        int f1 = features.features[i][side_to_move];
        int f2 = features.features[i][!side_to_move];
        for (int j = 0; j < hidden_size; ++j) {
            gradient.input_features[f1 * hidden_size + j] += components[i];
            gradient.input_features[f2 * hidden_size + j] += components[hidden_size + i];
        }
    }
}

void Neural_network::load(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (file) {
        bool failed = false;
        if (!file.read(reinterpret_cast<char*>(input_features.data()), sizeof(input_features))) failed = true;
        if (!file.read(reinterpret_cast<char*>(input_bias.data()), sizeof(input_bias))) failed = true;
        if (!file.read(reinterpret_cast<char*>(hidden_features.data()), sizeof(hidden_features))) failed = true;
        if (!file.read(reinterpret_cast<char*>(hidden_bias.data()), sizeof(hidden_bias))) failed = true;
        if (failed) {
            std::cout << "error: checkpoint data size mismatch in " << path << std::endl;
            exit(0);
        }
        std::cout << "loaded checkpoint file " << path << std::endl;
    } else {
        std::cout << "couldn't read checkpoint file " << path << std::endl;
    }
}

void Neural_network::save(const std::string& path) {
    std::ofstream file(path, std::ios::binary);
    if (file) {
        file.write(reinterpret_cast<char*>(input_features.data()), sizeof(input_features));
        file.write(reinterpret_cast<char*>(input_bias.data()), sizeof(input_bias));
        file.write(reinterpret_cast<char*>(hidden_features.data()), sizeof(hidden_features));
        file.write(reinterpret_cast<char*>(hidden_bias.data()), sizeof(hidden_bias));
    } else {
        std::cout << "couldn't write checkpoint file " << path << std::endl;
    }
}

void Neural_network::quantize(const std::string& path, bool print){
    /*std::unique_ptr<Quantized_neural_network> qnn = std::make_unique<Quantized_neural_network>(*this, print);
    qnn->save(path);
    if (print) {
        std::cout << "quantized network saved to " << path << std::endl;
    }*/
}