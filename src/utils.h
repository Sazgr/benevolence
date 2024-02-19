#ifndef BENEVOLENCE_UTILS
#define BENEVOLENCE_UTILS

#include <cmath>

template<typename T = float>
inline const T sigmoid(const T x){
    return 1 / (1 + expf(-x));
}

template<typename T = float>
inline const T sigmoid_prime(const T x){
    T sig = sigmoid(x);
    return sig * (1 - sig);
}

inline float expected_eval(float eval, float wdl, float lambda) {
    return lambda * sigmoid(eval) + (1 - lambda) * wdl;
}

inline float error_function(float output, float expected) {
    return pow(sigmoid(output) - expected, 2);
}

inline float error_gradient(float output, float expected) {
    return 2 * (sigmoid(output) - expected);
}

#endif