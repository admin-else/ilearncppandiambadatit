#pragma once
#include <stdexcept>

struct GameError final : std::runtime_error {
    using runtime_error::runtime_error;
};