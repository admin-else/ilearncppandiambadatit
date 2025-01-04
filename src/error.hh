#pragma once
#include <stdexcept>

struct GameError: std::runtime_error {
    using runtime_error::runtime_error;
};