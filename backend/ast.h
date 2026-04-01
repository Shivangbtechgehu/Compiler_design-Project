#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>

// Base class for all nodes
struct ASTNode {
    virtual ~ASTNode() = default;
};

// Node for "Create integer x." [cite: 63]
struct VarDeclNode : public ASTNode {
    std::string varName;
    std::string type; // Always "int" for now
};

// Node for "Set x to 10." [cite: 64]
struct AssignmentNode : public ASTNode {
    std::string varName;
    int value;
};

// Node for "Print x." [cite: 65]
struct PrintNode : public ASTNode {
    std::string varName;
};

// The root of the program - a list of statements [cite: 69]
struct ProgramNode : public ASTNode {
    std::vector<std::unique_ptr<ASTNode>> statements;
};

// Node for "If x is greater than 5 then Print x."
struct IfNode : public ASTNode {
    std::string conditionVar;
    int conditionValue;
    std::unique_ptr<ASTNode> action; // The command to execute if true
};

// Node for "Repeat 3 times: Print x."
struct RepeatNode : public ASTNode {
    int count;
    std::unique_ptr<ASTNode> action; // The command to repeat
};

#endif