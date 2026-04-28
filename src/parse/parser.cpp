#include "parse/parser.hpp"
#include <stdexcept>

// -------------------------
// Top-level parse()
// -------------------------
std::unique_ptr<ASTNode> Parser::parse() {
    auto ast = expression();
    if (!is_at_end()) {
        throw std::runtime_error("Unexpected tokens after expression");
    }
    return ast;
}

// -------------------------
// Expression entry point
// -------------------------
std::unique_ptr<ASTNode> Parser::expression() {
    return parse_binary(0);
}

// -------------------------
// Precedence-climbing binary parser
// -------------------------
std::unique_ptr<ASTNode> Parser::parse_binary(int min_prec) {
    auto left = unary();

    while (!is_at_end() && peek() && peek()->type == TokenType::OPERATOR) {
        std::string op = peek()->lexeme;

        // Skip unary-only operators
        if (!registry.is_binary(op))
            break;

        int prec = registry.get_precedence(op);
        if (prec < min_prec)
            break;

        Associativity assoc = registry.get_associativity(op);
        int next_min_prec = prec + (assoc == Associativity::LEFT ? 1 : 0);

        advance(); // consume operator
        auto right = parse_binary(next_min_prec);

        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }

    return left;
}

// -------------------------
// Unary operator parsing
// -------------------------
std::unique_ptr<ASTNode> Parser::unary() {
    if (peek() && peek()->type == TokenType::OPERATOR) {
        std::string op = peek()->lexeme;

        if (registry.is_unary(op)) {
            advance();
            auto operand = unary();
            return std::make_unique<UnaryOpNode>(op, std::move(operand));
        }
    }

    return primary();
}

// -------------------------
// Primary expressions
// -------------------------
std::unique_ptr<ASTNode> Parser::primary() {
    // NUMBER
    if (peek() && peek()->type == TokenType::NUMBER) {
        Token* token = advance();
        return std::make_unique<LiteralNode>(token->literal);
    }

    // IDENTIFIER (constants only)
    if (peek() && peek()->type == TokenType::IDENTIFIER) {
        Token* token = advance();
        if (registry.is_const(token->lexeme)) {
            return std::make_unique<ConstantNode>(token->lexeme);
        }
        throw std::runtime_error("Unknown identifier: " + token->lexeme);
    }

    // FUNCTION CALL
    if (peek() && peek()->type == TokenType::FUNCTION) {
        Token* token = advance();
        std::string name = token->lexeme;

        if (!match(TokenType::LPAREN))
            throw std::runtime_error("Expected ( after function");

        std::vector<std::unique_ptr<ASTNode>> args;

        if (!match(TokenType::RPAREN)) {
            do {
                args.push_back(expression());
            } while (match(TokenType::COMMA));

            if (!match(TokenType::RPAREN))
                throw std::runtime_error("Expected ) after arguments");
        }

        return std::make_unique<FunctionCallNode>(name, std::move(args));
    }

    // PARENTHESIZED EXPRESSION
    if (match(TokenType::LPAREN)) {
        auto expr = expression();
        if (!match(TokenType::RPAREN))
            throw std::runtime_error("Expected )");
        return expr;
    }

    // ERROR
    Token* token = peek();
    throw std::runtime_error("Unexpected token: " + (token ? token->lexeme : "EOF"));
}

// -------------------------
// Token utilities
// -------------------------
Token* Parser::peek() {
    if (is_at_end()) return nullptr;
    return tokens[current];
}

Token* Parser::advance() {
    if (!is_at_end()) current++;
    return tokens[current - 1];
}

bool Parser::match(TokenType type) {
    if (is_at_end() || !peek() || peek()->type != type)
        return false;
    advance();
    return true;
}

bool Parser::is_at_end() const {
    return current >= tokens.size() ||
           tokens[current]->type == TokenType::EOF_TOKEN;
}
