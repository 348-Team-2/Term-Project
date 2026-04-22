/**
* @file def_const.hpp
 * @brief Defines the structural blueprint for mathematical constants.
 * @details This file provides the ConstantStruct used to store immutable
 * mathematical values (e.g., pi, e, phi) within the Registry. By using
 * the universal Value type, constants can represent not just scalars,
 * but also constant matrices or vectors if required by the system.
 */

#pragma once

#include <string>
#include "def_value.hpp" // Bring in the Value type

/// @brief Static mathematical constant
struct ConstantStruct
{
    /// @brief The string identifier for the constant
    std::string name;

    /// @brief The immutable value of the constant (can be Scalar, Matrix, etc.)
    Value value;
};