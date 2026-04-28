#pragma once

#include <vector>
#include <string>
#include <memory>
#include <cmath>


// ======================================================
// AST BASE CLASS
// ======================================================

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual Value evaluate(const Registry& reg) const = 0;
    virtual std::vector<std::string> to_list() const = 0;
};

// ======================================================
// LITERAL NODE
// ======================================================

struct LiteralNode : public ASTNode {
    Value value;

    explicit LiteralNode(Value v)
        : value(std::move(v)) {}

    Value evaluate(const Registry&) const override {
        return value;
    }

    std::vector<std::string> to_list() const override {
        if (std::holds_alternative<double>(value)) {
            double d = std::get<double>(value);
            if (d == std::floor(d)) {
                return {std::to_string(static_cast<long long>(d))};
            } else {
                return {std::to_string(d)};
            }
        }
        return {"literal"}; // placeholder for other types
    }
};

// ======================================================
// BINARY OPERATOR NODE
// ======================================================

struct BinaryOpNode : public ASTNode {
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    BinaryOpNode(std::string o,
                 std::unique_ptr<ASTNode> l,
                 std::unique_ptr<ASTNode> r)
        : op(std::move(o)),
          left(std::move(l)),
          right(std::move(r)) {}

    Value evaluate(const Registry& reg) const override {
        return reg.evaluate_binary(op,
                                   left->evaluate(reg),
                                   right->evaluate(reg));
    }

    std::vector<std::string> to_list() const override {
        auto l = left->to_list();
        auto r = right->to_list();
        l.insert(l.end(), r.begin(), r.end());
        l.push_back(op);
        return l;
    }
};

// ======================================================
// UNARY OPERATOR NODE
// ======================================================

struct UnaryOpNode : public ASTNode {
    std::string op;
    std::unique_ptr<ASTNode> operand;

    UnaryOpNode(std::string o,
                std::unique_ptr<ASTNode> opnd)
        : op(std::move(o)),
          operand(std::move(opnd)) {}

    Value evaluate(const Registry& reg) const override {
        return reg.evaluate_unary(op,
                                  operand->evaluate(reg));
    }

    std::vector<std::string> to_list() const override {
        auto o = operand->to_list();
        o.push_back(op);
        return o;
    }
};

// ======================================================
// FUNCTION CALL NODE
// ======================================================

struct FunctionCallNode : public ASTNode {
    std::string name;
    std::vector<std::unique_ptr<ASTNode>> args;

    FunctionCallNode(std::string n,
                     std::vector<std::unique_ptr<ASTNode>> a)
        : name(std::move(n)),
          args(std::move(a)) {}

    Value evaluate(const Registry& reg) const override {
        std::vector<Value> vals;
        vals.reserve(args.size());
        for (const auto& arg : args)
            vals.push_back(arg->evaluate(reg));
        return reg.evaluate_function(name, vals);
    }

    std::vector<std::string> to_list() const override {
        std::vector<std::string> result;
        for (const auto& arg : args) {
            auto arg_list = arg->to_list();
            result.insert(result.end(), arg_list.begin(), arg_list.end());
        }
        result.push_back(name);
        return result;
    }
};

// ======================================================
// CONSTANT NODE
// ======================================================

struct ConstantNode : public ASTNode {
    std::string name;

    explicit ConstantNode(std::string n)
        : name(std::move(n)) {}

    Value evaluate(const Registry& reg) const override {
        return reg.get_constant(name);
    }

    std::vector<std::string> to_list() const override {
        return {name};
    }
};

// ======================================================
// PARSER CLASS
// ======================================================

class Parser {
private:
    std::vector<Token*> tokens;
    size_t current = 0;
    Registry& registry;

public:
    Parser(std::vector<Token*>& t, Registry& r)
        : tokens(t), registry(r) {}

    std::unique_ptr<ASTNode> parse();

private:
    std::unique_ptr<ASTNode> expression();
    std::unique_ptr<ASTNode> parse_binary(int min_precedence);
    std::unique_ptr<ASTNode> unary();
    std::unique_ptr<ASTNode> primary();

    Token* peek();
    Token* advance();
    bool match(TokenType type);

    // MUST be const to match parser.cpp
    bool is_at_end() const;
};
