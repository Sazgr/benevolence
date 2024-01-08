#ifndef BENEVOLENCE_ACTIVATION
#define BENEVOLENCE_ACTIVATION

#include <algorithm>

template <typename T>
class Relu {
    T operator()(const T x) {
        return std::max<T>(0, x);
    }
    T prime(const T x) {
        return x > 0 ? 1 : 0;
    }
};

template <typename T>
class Crelu {
    T operator()(const T x) {
        return std::clamp<T>(0, x);
    }
    T prime(const T x) {
        return (x > 0 && x < 1) ? 1 : 0;
    }
};

template <typename T>
class Screlu {
    T operator()(const T x) {
        T clipped = std::clamp<T>(0, x);
        return clipped * clipped;
    }
    T prime(const T x) {
        return (x > 0 && x < 1) ? (2 * x) : 0;
    }
};

#endif
