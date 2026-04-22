#pragma once

#include <string>
#include "Def_Value.hpp" // Bring in the Value type

/// @brief Static mathematical constant
struct ConstantStruct
{
    /// @brief The string identifier for the constant
    std::string name;

    /// @brief The immutable value of the constant (can be Scalar, Matrix, etc.)
    Value value;
};