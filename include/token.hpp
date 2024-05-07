#pragma once

#include <string>

struct Token {
	enum Type{
		INTEGER_LITERAL, FLOAT_LITERAL, CHAR_LITERAL, BOOL_LITERAL, STRING_LITERAL, POINTER_LITERAL,
		IDENTIFIER, KEYWORD, TYPE,
		SPECIAL,
		INVALID, END
	} type;

	std::string value;

	Token(Type type, const std::string& value) : type(type), value(value) {}

	bool operator==(Type other_type) const {
		return type == other_type;
	}

	bool operator==(const std::string& other_value) const {
		return value == other_value;
	}
};