#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

#include "def_const.hpp"
#include "def_funct.hpp"
#include "def_operator.hpp"

/// @brief Centralized storage of all language rules and operations
/// @note Singleton
class Registry {

    /// @brief Maps of operators / constants / functions
    std::unordered_map<std::string, OperatorStruct> operators;
    std::unordered_map<std::string, ConstantStruct> constants;
    std::unordered_map<std::string, FunctionStruct> functions;

public:
    Registry() = default;
    ~Registry() = default;

    // ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

    /// @brief Loads a new operator definition into the system memory.
    /// @param def The populated OperatorStruct struct containing precedence and execution logic.
    void register_operator(const OperatorStruct& def);

    /// @brief Loads a built-in mathematical constant into the system memory.
    /// @param def The populated ConstantStruct struct.
    void register_constant(const ConstantStruct& def);

    /// @brief Loads a standard mathematical function into the system memory.
    /// @param def The populated FunctionStruct struct.
    void register_function(const FunctionStruct& def);

    // ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

    /// @brief Checks if a parsed token string matches any registered operator.
    /// @param symbol The raw string from the token (e.g., "+").
    /// @return true if the operator exists in the registry, false otherwise.
    bool is_operator(const std::string& symbol) const;

    /// @brief Retrieves the precedence level of a registered operator to build the AST.
    /// @param symbol The operator string to query.
    /// @return The integer precedence level.
    /// @throws std::invalid_argument If the requested operator does not exist.
    int get_precedence(const std::string& symbol) const;

    /// @brief Retrieves the binding direction of a registered operator.
    /// @param symbol The operator string to query.
    /// @return The Associativity enum value (LEFT, RIGHT, NONE).
    /// @throws std::invalid_argument If the requested operator does not exist.
    Associativity get_associativity(const std::string& symbol) const;

    // ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

    /// @brief Executes specific binary operator
    /// @param symbol The operator string dictating the math logic
    /// @param left Left operand
    /// @param right Right operand
    /// @return Evaluated double
    /// @throws std::invalid_argument If symbol not registered or not binary
    /// @throws std::runtime_error If math reaches invalid state
    double evaluate_binary(const std::string& symbol, double left, double right) const;

    /// @brief Executes specific binary operator
    /// @param symbol The operator string dictating the math logic
    /// @param operand
    /// @return The evaluated double.
    /// @throws std::invalid_argument If the operator symbol is not registered or isn't unary.
    double evaluate_unary(const std::string& symbol, double operand) const;

    /// @brief Executes the stored mathematical logic for a specific function.
    /// @param name The function string identifier.
    /// @param args The vector of evaluated numeric arguments.
    /// @return The calculated double.
    /// @throws std::invalid_argument If the function is not registered or argument count is wrong.
    double evaluate_function(const std::string& name, const std::vector<double>& args) const;

    /// @brief Retrieves the numeric value of a stored constant.
    /// @param name The string identifier of the constant.
    /// @return The precise double value.
    /// @throws std::invalid_argument If the constant is not registered.
    double get_constant(const std::string& name) const;
};