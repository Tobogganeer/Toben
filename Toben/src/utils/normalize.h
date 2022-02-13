#pragma once

// https://stackoverflow.com/questions/37580501/normalized-integer-to-from-float-conversion

#include <cstdint>
#include <limits>

template <typename T>
constexpr double normalize(T value) {
    return value < 0
        ? -static_cast<double>(value) / std::numeric_limits<T>::min()
        : static_cast<double>(value) / std::numeric_limits<T>::max()
        ;
}