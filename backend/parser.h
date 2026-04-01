#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include "lexer.h"
#include "ast.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    
    // The main function that starts the parsing process
    std::unique_ptr<ProgramNode> parseProgram();

private:
    std::vector<Token> tokens;
    size_t position;

    // Helper functions to navigate tokens
    Token currentToken();
    Token peekNextToken();
    void advance();
    void expect(TokenType expectedType, const std::string& errorMessage);

    // Parsing rules for your specific English grammar
    std::unique_ptr<ASTNode> parseStatement();
    std::unique_ptr<ASTNode> parseVariableDeclaration();
    std::unique_ptr<ASTNode> parseAssignment();
    std::unique_ptr<ASTNode> parsePrint();
    std::unique_ptr<ASTNode> parseIfStatement();
    std::unique_ptr<ASTNode> parseRepeatStatement();
};

#endif