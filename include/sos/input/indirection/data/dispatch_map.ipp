#pragma once

#include <functional>
#include <unordered_map>

namespace sos::input::indirection::__data__ {
template <typename input_type>
static inline std::unordered_map<input_type, std::function<void(input_type)>>
    dispatch_map;
}
