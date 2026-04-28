/**
* @file lexer.hpp
 * @brief Declares the Lexer class which tokenizes input.
 * @details This header defines the Lexer component of the calculator.
 */


 /**
 * @class Lexer
 * @brief Tokenizes input for the calculator.
 * @details This class is responsible for converting input strings into a sequence of tokens.
 */

class Lexer {
public:

    /// @brief Tokenizes the input string.
    void tokenize(const std::string& input);

};