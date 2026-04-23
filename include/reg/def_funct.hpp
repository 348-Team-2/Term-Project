/**
* @file def_funct.hpp
 * @brief Defines the structural blueprint for n-ary mathematical functions.
 * @details This file provides the FunctionStruct, which allows the Registry
 * to store and execute named functions (e.g., sin, max, clamp). It utilizes
 * a std::vector of Value types to support a variable number of arguments,
 * enabling the system to handle everything from unary trigonometric functions
 * to complex multi-argument operations.
 */

#pragma once

#include <string>
#include <vector>
#include <functional>
#include "def_value.hpp"

/// @brief n-ary mathematical function
/// @note Allows an arbitrary number of arguments passed via vector
struct FunctionStruct
{
    /// @brief The string identifier for the function
    std::string name;

    /// @brief The exact number of arguments
    int expected_args;

    /// @brief The executable logic for the function
    /// @param args A vector containing the evaluated arguments (Scalars, Vectors, etc.)
    /// @return The calculated result as a Value
    /// @throws std::invalid_argument if size of args does not match expected_args
    /// @throws std::runtime_error for invalid arguments
    std::function<Value(const std::vector<Value>&)> evaluate;
};