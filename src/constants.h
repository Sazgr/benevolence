#ifndef BENEVOLENCE_CONSTANTS
#define BENEVOLENCE_CONSTANTS

#include "types.h"

constexpr int batch_size = 16384;

constexpr int buckets = 1;
constexpr int input_size = 12 * 64 * buckets;
constexpr int hidden_size = 512;
constexpr int output_size = 1;
constexpr int input_quantization = 255;
constexpr int hidden_quantization = 64;

constexpr float eval_scale = 400.0f;
constexpr float eval_cp_ratio = 0.7f;

constexpr int threads = 8;

constexpr u64 epoch_size = 1e8;
constexpr u64 val_epoch_size = 1e7;

#endif