#include <string>
#include <vector>
#include <memory>

#include "token.hpp"
#include "ast.hpp"

class Interpreter {
public:
	void interpret(const std::string&);
	void interpret_file(const std::string&);
private:
	std::vector<Token> tokenize(const std::string&);
	std::shared_ptr<TranslationUnit> parse(const std::vector<Token>&);
};
