#include "parser.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), position(0) {}

Token Parser::currentToken() {
    if (position >= tokens.size()) return {TOKEN_EOF, ""};
    return tokens[position];
}

void Parser::advance() {
    if (position < tokens.size()) position++;
}

// Crucial: This enforces your strict grammar rules
void Parser::expect(TokenType expectedType, const std::string& errorMessage) {
    if (currentToken().type == expectedType) {
        advance();
    } else {
        throw std::runtime_error("Syntax Error: " + errorMessage + " Found: " + currentToken().value);
    }
}

std::unique_ptr<ProgramNode> Parser::parseProgram() {
    auto program = std::make_unique<ProgramNode>();
    
    // Keep parsing statements until we hit the end of the file
    while (currentToken().type != TOKEN_EOF) {
        program->statements.push_back(parseStatement());
    }
    return program;
}

std::unique_ptr<ASTNode> Parser::parseStatement() {
    Token token = currentToken();

    // Look at the first word to decide what kind of sentence this is
    if (token.type == TOKEN_CREATE) {
        return parseVariableDeclaration();
    } else if (token.type == TOKEN_SET) {
        return parseAssignment();
    } else if (token.type == TOKEN_PRINT) {
        return parsePrint();
    } else {
        throw std::runtime_error("Syntax Error: Unknown command starting with '" + token.value + "'");
    }
}

// Rule: "Create integer [identifier]."
std::unique_ptr<ASTNode> Parser::parseVariableDeclaration() {
    auto node = std::make_unique<VarDeclNode>();
    
    expect(TOKEN_CREATE, "Expected 'Create'");
    expect(TOKEN_INTEGER, "Expected 'integer'");
    
    node->type = "int";
    node->varName = currentToken().value;
    expect(TOKEN_IDENTIFIER, "Expected a variable name");
    
    expect(TOKEN_PERIOD, "Expected '.' at the end of the sentence");
    
    return node;
}

// Rule: "Set [identifier] to [number]."
std::unique_ptr<ASTNode> Parser::parseAssignment() {
    auto node = std::make_unique<AssignmentNode>();
    
    expect(TOKEN_SET, "Expected 'Set'");
    
    node->varName = currentToken().value;
    expect(TOKEN_IDENTIFIER, "Expected a variable name");
    
    expect(TOKEN_TO, "Expected 'to'");
    
    node->value = std::stoi(currentToken().value); // Convert string number to int
    expect(TOKEN_NUMBER, "Expected a number");
    
    expect(TOKEN_PERIOD, "Expected '.' at the end of the sentence");
    
    return node;
}

// Rule: "Print [identifier]."
std::unique_ptr<ASTNode> Parser::parsePrint() {
    auto node = std::make_unique<PrintNode>();
    
    expect(TOKEN_PRINT, "Expected 'Print'");
    
    node->varName = currentToken().value;
    expect(TOKEN_IDENTIFIER, "Expected a variable name to print");
    
    expect(TOKEN_PERIOD, "Expected '.' at the end of the sentence");
    
    return node;
}