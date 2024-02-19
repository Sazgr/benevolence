#ifndef BENEVOLENCE_ACTIVATION
#define BENEVOLENCE_ACTIVATION

#include <algorithm>

template <typename T>
class Relu {
public:
    T operator()(const T x) const {
        return std::max<T>(0, x);
    }
    T prime(const T x) const {
        return x > 0 ? 1 : 0;
    }
};

template <typename T>
class Crelu {
public:
    T operator()(const T x) const {
        return std::clamp<T>(x, 0, 1);
    }
    T prime(const T x) const {
        return (x > 0 && x < 1) ? 1 : 0;
    }
};

template <typename T>
class Screlu {
public:
    T operator()(const T x) const {
        T clipped = std::clamp<T>(x, 0, 1);
        return clipped * clipped;
    }
    T prime(const T x) const {
        return (x > 0 && x < 1) ? (2 * x) : 0;
    }
};

#endif
