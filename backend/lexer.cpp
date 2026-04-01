#include "lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& source) : sourceCode(source), position(0) {
    // Populate the keyword dictionary
    keywords["Create"] = TOKEN_CREATE;
    keywords["integer"] = TOKEN_INTEGER;
    keywords["Set"] = TOKEN_SET;
    keywords["to"] = TOKEN_TO;
    keywords["If"] = TOKEN_IF;
    keywords["is"] = TOKEN_IS;
    keywords["greater"] = TOKEN_GREATER;
    keywords["than"] = TOKEN_THAN;
    keywords["then"] = TOKEN_THEN;
    keywords["Print"] = TOKEN_PRINT;
    keywords["Repeat"] = TOKEN_REPEAT;
    keywords["times"] = TOKEN_TIMES;
}

char Lexer::peek() {
    if (position >= sourceCode.length()) return '\0';
    return sourceCode[position];
}

char Lexer::advance() {
    if (position >= sourceCode.length()) return '\0';
    return sourceCode[position++];
}

void Lexer::skipWhitespace() {
    while (std::isspace(peek())) {
        advance();
    }
}

Token Lexer::readNumber() {
    std::string numStr = "";
    while (std::isdigit(peek())) {
        numStr += advance();
    }
    return {TOKEN_NUMBER, numStr};
}

Token Lexer::readWord() {
    std::string word = "";
    while (std::isalnum(peek())) {
        word += advance();
    }
    
    // Check if the word is a known keyword
    if (keywords.find(word) != keywords.end()) {
        return {keywords[word], word};
    }
    
    // If not a keyword, it's a variable name (identifier)
    return {TOKEN_IDENTIFIER, word};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (position < sourceCode.length()) {
        skipWhitespace();
        char currentChar = peek();

        if (currentChar == '\0') {
            break;
        }

        if (std::isdigit(currentChar)) {
            tokens.push_back(readNumber());
        } 
        else if (std::isalpha(currentChar)) {
            tokens.push_back(readWord());
        } 
        else if (currentChar == '.') {
            tokens.push_back({TOKEN_PERIOD, "."});
            advance();
        } 
        else if (currentChar == ':') {
            tokens.push_back({TOKEN_COLON, ":"});
            advance();
        } 
        else {
            // Unknown character
            std::string unknownStr(1, currentChar);
            tokens.push_back({TOKEN_UNKNOWN, unknownStr});
            advance();
        }
    }

    tokens.push_back({TOKEN_EOF, ""});
    return tokens;
}