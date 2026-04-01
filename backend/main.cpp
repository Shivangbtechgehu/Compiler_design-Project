#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.h"
#include "parser.h"

int main() {
    std::ifstream file("test_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open test_input.txt" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    try {
        // 1. Lexical Analysis
        Lexer lexer(source);
        std::vector<Token> tokens = lexer.tokenize();
        std::cout << "Lexical Analysis: Success!" << std::endl;

        // 2. Syntax Analysis (Parsing)
        Parser parser(tokens);
        std::unique_ptr<ProgramNode> ast = parser.parseProgram();
        
        std::cout << "Parsing: Success! The AST has been built." << std::endl;
        std::cout << "Successfully parsed " << ast->statements.size() << " statements." << std::endl;

    } catch (const std::exception& e) {
        // This will print our custom syntax errors if the grammar is wrong!
        std::cerr << e.what() << std::endl; 
    }

    return 0;
}