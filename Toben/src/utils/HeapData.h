#pragma once

#include <memory>

template<typename T>
using HeapScope = std::unique_ptr<T>;

template<typename T>
using HeapRef = std::shared_ptr<T>;