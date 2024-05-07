#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

#include "lexer.hpp"

Lexer::Lexer(const std::string& input) : input(input) {}

std::vector<Token> Lexer::tokenize() {
	std::vector<Token> tokens;

	for (; input[offset];) {
		if (std::isspace(input[offset])) {
			++offset;
		} else if (std::isalpha(input[offset]) || input[offset] == '_') {
			tokens.push_back(extract_identifier());
		} else if (std::isdigit(input[offset]) || input[offset] == '.') {
			tokens.push_back(extract_number());
		} else if (input[offset] == '\'') {
			tokens.push_back(extract_char());
		} else if (input[offset] == '"') {
			tokens.push_back(extract_string());
		} else if (metachars.contains(input[offset])) {
			tokens.push_back(extract_operator());
		}  else if (input.substr(offset, 2) == "//") {
			skip_line_comment();
		} else if (input.substr(offset, 2) == "/*") {
			skip_multiline_comment();
		} else {
			throw std::runtime_error("Unknown character " + input[offset]);
		}
	}
	tokens.push_back(Token{Token::END, ""});
	return tokens;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Token Lexer::extract_identifier() {
	std::size_t size;
	for (size = 0; std::isalnum(input[offset + size]) || input[offset + size] == '_'; ++size);
	std::string identifier(input, offset, size);
	offset += size;
	if (keywords.contains(identifier)) {
		return Token{Token::KEYWORD, identifier};
	} else if (types.contains(identifier)) {
		return Token{Token::TYPE, identifier};
	} else if (identifier == "true" || identifier == "false") {
		return Token{Token::BOOL_LITERAL, identifier};
	}
	return Token{Token::IDENTIFIER, identifier};
}

Token Lexer::extract_number() {
	std::size_t size;
	for (size = 0; std::isdigit(input[offset + size]); ++size);
	if (input[offset + size] == '.') {
		++size;
		for (; std::isdigit(input[offset + size]); ++size);
		if (size == 1) {
			throw std::runtime_error("Invalid floating-point literal");
		}
		offset += size;
		return Token{Token::FLOAT_LITERAL, std::string(input, offset, size)};
	}
	auto num = std::string(input, offset, size);
	offset += size;
	return Token{Token::INTEGER_LITERAL, num};
}

Token Lexer::extract_char() {
	//return Token{};
}

Token Lexer::extract_string() {
	//return Token{};
}

Token Lexer::extract_operator() {
	std::size_t size;
	std::string op;
	for (size = 0; metachars.contains(input[offset + size]); ++size) {
		op.push_back(input[offset + size]);
		if (!tokens_dictionary.contains(op)) {
			if (size == 0) {
				throw std::runtime_error("Invalid operator");
			}
			op.pop_back();
			break;
		}
	}
	offset += size;
	return Token{tokens_dictionary.at(op), op};
}

void Lexer::skip_line_comment() {
	for(; input[offset] != '\n'; ++offset);
}

void Lexer::skip_multiline_comment() {
	for(; input.substr(offset, 2) != "*/"; ++offset) {
		if (input[offset] == '\0') {
			throw std::runtime_error("Unclosed multiline comment");
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::string Lexer::metachars = "+-*/%^=<>&|!(){}[],;";

const std::unordered_set<std::string> Lexer::keywords = {
	"if", "else", "while", "for", "return", "break", "continue"
};

const std::unordered_set<std::string> Lexer::types = {
	"int", "double", "char", "string", "bool", "void"
};

const std::unordered_set<std::string> Lexer::specials = {
	"+", "-", "*", "/", "%", "**",
	"++", "--",
	"&",
	"&&", "||", "!",
	"==", "!=", ">", "<", ">=", "<=",
	"=", "+=", "-=", "*=", "/=", "%=", "**=",
	",", ".", ";", "(", ")", "{", "}", "[", "]"
};