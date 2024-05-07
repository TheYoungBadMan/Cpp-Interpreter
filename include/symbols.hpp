#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class Object {
protected:
	std::shared_ptr<Type> type;
	int scope_level;
};

class Variable : public Object {
	std::shared_ptr<Value> value;
	bool is_initialized;
};

class Function : public Object {
	std::vector<std::shared_ptr<Type>> parameters;
	std::shared_ptr<CompoundStatement> body;
};


class Scope {
	std::unordered_map<std::string, SymbolInfo>
};

class SymbolTable {
	std::vector<Scope> scopes;
};