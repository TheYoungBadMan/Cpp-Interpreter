#include <iostream>
#include <fstream>
#include <sstream>

#include "interpreter.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "printer.hpp"

void Interpreter::interpret(const std::string& source_code) {
	try {
		auto tokens = tokenize(source_code);
		auto root = parse(tokens);
		Printer printer;
		root->accept(printer);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void Interpreter::interpret_file(const std::string& filepath) {
	std::ifstream file(filepath);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filepath << std::endl;
		return;
	}

	std::stringstream input;
	input << file.rdbuf();
	interpret(input.str());
}

std::vector<Token> Interpreter::tokenize(const std::string& sourceCode) {
    // Delegate to the Lexer to generate tokens from the source code
    return Lexer(sourceCode).tokenize();
}

std::shared_ptr<TranslationUnit> Interpreter::parse(const std::vector<Token>& tokens) {
    // Use the Parser to generate an AST from the tokens
    return Parser(tokens).parse();
}