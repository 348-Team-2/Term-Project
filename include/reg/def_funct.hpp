#pragma once

#include <string>
#include <vector>
#include <functional>

/// @brief n-ary mathematical function
/// @note Allows an arbitrary number of arguments passed via vector
struct FunctionStruct
{
    /// @brief The string identifier for the function
    std::string name;

    /// @brief The exact number of arguments
    int expected_args;

    /// @brief The executable logic for the function
    /// @param args A vector containing the evaluated numeric arguments
    /// @return The calculated result
    /// @throws std::invalid_argument if size of args does not match expected_args
    /// @throws std::runtime_error for invalid arguments
    std::function<double(const std::vector<double>&)> evaluate;
};