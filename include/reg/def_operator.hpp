#pragma once

#include <string>
#include <functional>

#include "def_value.hpp"

// TODO: IDEA Estimate if there will be float/double mistakes?

/// @brief Defines associativity for parser AST construction
enum class Associativity {
    LEFT,
    RIGHT,
    NONE, ///< Used for unary operators
};

/// @brief Blueprint for mathematical operators
/// @note Decouples mathematical logic from core program
struct OperatorStruct
{
    /// @brief The string representation of the operator (e.g., "+", "**", "?")
    std::string symbol;

    /// @brief The priority level of operator
    int precedence;

    Associativity associativity;

    /// @brief Flag to determine if operator takes only one operand
    bool is_unary;

    /// @brief The executable logic for a binary operation
    /// @param a The left operand
    /// @param b The right operand
    /// @return The calculated result of the operation
    /// @throws std::runtime_error for invalid math states
    std::function<Value(const Value&, const Value&)> evaluate_binary;

    /// @brief The executable logic for a unary operation
    /// @param a The single operand
    /// @return The calculated result
    /// @warning See evaluate_binary
    std::function<Value(const Value&)> evaluate_unary;
};