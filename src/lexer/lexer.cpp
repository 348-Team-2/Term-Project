#include <def_const.hpp>
#include "token.hpp"
#include "def_cli.hpp"


// CREATE CLASS
    // list of tokens should be a private variable of the class
    // Create methods that perform the different steps of the lexer (e.g., tokenize, is_number, is_operator, etc.)

// STEPS:
// 1. Receive user input from command line interface (CLI).
// 2. Create list of tokens from the input string using the Lexer.

// 2

std::vector<Token*> tokens;


// This is how you create a token
//std::string temp_str = "2+3*4\n";

//Token* token1 = new Token(TokenType::NUMBER, "2", new Value(2), 1, 4);

class Lexer {
    private:
        std::vector<Token*> tokens;
        std::string temp_str = "2+3*4\n";
    public:
        // functions to call
            // 
        void tokenize(const std::string& input) {
            // Tokenization logic goes here
            char single_char_operators[] = {'+', '-', '/', '*', '^', '(', ')'};
            char functions[3][3] = {{'s', 'i', 'n'}, {'c', 'o', 's'}, {'t', 'a', 'n'}};
            char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
            char two_digit_constants[1][2] = {{'p', 'i'}};
            char single_char_constants[2] = {'e', 'i'};
            char structural_delimiters[] = {'(', ')', ','};

            char current_char;
            char next_char;
            char prev_char;
            std::vector<char> curr_expression;
            int i = 0;
            while (current_char != '\'' && next_char != 'n') {
                char current_char = input[i];
                char next_char = input[i+1];
                // handle ** operator first since it is two characters and we don't want to accidentally tokenize the first * as a single operator
                if (current_char == '*' && next_char == '*') {
                    // Create a token for the exponentiation operator
                    Token* new_token = new Token(TokenType::OPERATOR, "**");
                    tokens.push_back(new_token);
                    i++; // Skip the next character since it's part of the operator
                    continue; // Move to the next iteration
                }
                // Check if the current character is a single-character operator
                if (is_operator(current_char)) {
                    // Create a token for the operator, and add it to the tokens vector
                    Token* new_token = new Token(TokenType::OPERATOR, current_char); // Should I add more parameters for operators?
                    tokens.push_back(new_token);
                    i++; // Move to the next character
                    continue; // Move to the next iteration
                }

                // Next three if statements check for structural delimiters (parentheses and commas) and create tokens for them. We need to check for these before functions and constants since they can be part of function calls (e.g., sin(x)) and we want to make sure we tokenize the parentheses correctly.
                if (current_char == '(') {
                    // Create a token for the left parenthesis
                    Token* new_token = new Token(TokenType::LPAREN, "(");
                    tokens.push_back(new_token);
                    i++; // Move to the next character
                    continue; // Move to the next iteration
                }
                if (current_char == ')') {
                    // Create a token for the right parenthesis
                    Token* new_token = new Token(TokenType::RPAREN, ")");
                    tokens.push_back(new_token);
                    i++; // Move to the next character
                    continue; // Move to the next iteration
                }
                if (current_char == ',') {
                    // Create a token for the comma
                    Token* new_token = new Token(TokenType::COMMA, ",");
                    tokens.push_back(new_token);
                    i++; // Move to the next character
                    continue; // Move to the next iteration
                }


                // Next couple if statements check for functions and constants. If the current character and the next few characters match a function or constant name, we create a token for it and skip the appropriate number of characters.
                if (current_char == 's' && next_char == 'i' && input[i+2] == 'n') {
                    // Create a token for the sin function
                    Token* new_token = new Token(TokenType::FUNCTION, "sin");
                    tokens.push_back(new_token);
                    i += 3; // Skip the next two characters since they're part of the function name
                    continue; // Move to the next iteration
                }
                if (current_char == 'c' && next_char == 'o' && input[i+2] == 's') {
                    // Create a token for the cos function
                    Token* new_token = new Token(TokenType::FUNCTION, "cos");
                    tokens.push_back(new_token);
                    i += 3; // Skip the next two characters since they're part of the function name
                    continue; // Move to the next iteration
                }
                if (current_char == 't' && next_char == 'a' && input[i+2] == 'n') {
                    // Create a token for the tan function
                    Token* new_token = new Token(TokenType::FUNCTION, "tan");
                    tokens.push_back(new_token);
                    i += 3; // Skip the next two characters since they're part of the function name
                    continue; // Move to the next iteration
                }

                if (current_char == 'p' && next_char == 'i') {
                    // Create a token for the pi constant
                    Token* new_token = new Token(TokenType::IDENTIFIER, "pi", Value(3.141592653589793));
                    tokens.push_back(new_token);
                    i += 2; // Skip the next character since it's part of the constant name
                    continue; // Move to the next iteration
                }

                // Check if the current character is a digit (in the numbers array)
                // If the next character is also a digit, we need to keep reading until we reach the end of the number
                while(true) {
                    if (current_char == numbers[0] || current_char == numbers[1] || current_char == numbers[2] || current_char == numbers[3] || current_char == numbers[4] || current_char == numbers[5] || current_char == numbers[6] || current_char == numbers[7] || current_char == numbers[8] || current_char == numbers[9]) {
                        curr_expression.push_back(current_char);
                        i++;
                        current_char = input[i];
                    }
                    else {
                        // Create a token for the number, and add it to the tokens vector
                        // convert the curr_expression vector of chars to a string
                        std::string number_str(curr_expression.begin(), curr_expression.end());
                        // Token* new_token = new Token(TokenType::NUMBER, number_str, Value(std::stod(number_str)));
                        Token.new_token(TokenType::NUMBER, number_str, Value(std::stod(number_str)), 1, 1);
                        tokens.push_back(new_token);
                        break; // End of number reached
                    }
                }

                // Unknown Character
                Token.new_token(TokenType::UNKNOWN, current_char);
                tokens.push_back(new_token);
                i++; // Move to the next character
                

                // If the current char is a number, we need to check if the next char is also a number (to account for multi-digit numbers)
            }
            // tokenize the EOF Character at the end of the input string
            Token* new_token = new Token(TokenType::EOF_TOKEN, "\\n");
            tokens.push_back(new_token);
        }
};