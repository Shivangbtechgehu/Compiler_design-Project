#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <unordered_map>

// Define all possible token types based on your grammar
enum TokenType {
    TOKEN_CREATE, TOKEN_INTEGER, TOKEN_SET, TOKEN_TO,
    TOKEN_IF, TOKEN_IS, TOKEN_GREATER, TOKEN_THAN, TOKEN_THEN,
    TOKEN_PRINT, TOKEN_REPEAT, TOKEN_TIMES,
    TOKEN_IDENTIFIER, TOKEN_NUMBER, 
    TOKEN_PERIOD, TOKEN_COLON, TOKEN_EOF, TOKEN_UNKNOWN
};

// Struct to hold the token data
struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string sourceCode;
    size_t position;
    std::unordered_map<std::string, TokenType> keywords;

    char peek();
    char advance();
    void skipWhitespace();
    Token readNumber();
    Token readWord();
};

#endif