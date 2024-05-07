#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "token.hpp"

class Lexer {
public:
	Lexer(const std::string&);

	std::vector<Token> tokenize();

private:
	Token extract_identifier();
	Token extract_number();
	Token extract_char();
	Token extract_string();
	Token extract_operator();
	
	void skip_line_comment();
	void skip_multiline_comment();

	static const std::string metachars;
	static const std::unordered_set<std::string> keywords;
	static const std::unordered_set<std::string> types;
	static const std::unordered_set<std::string> specials;

	std::string input;
	std::size_t offset = 0;
};