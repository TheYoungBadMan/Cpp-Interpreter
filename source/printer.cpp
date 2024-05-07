#include <iostream>

#include "printer.hpp"

void Printer::visit(TranslationUnit& node) {
	for (auto& decl : node.declarations) {
		decl->accept(*this);
	}
	std::cout << std::endl;
}

void Printer::visit(Declaration::NoPtrDeclarator& node) {
	std::cout << node.name;
}

void Printer::visit(Declaration::PtrDeclarator& node) {
	std::cout << "*" << node.name;
}

void Printer::visit(Declaration::InitDeclarator& node) {
	node.declarator->accept(*this);
	if (node.initializer) {
		std::cout << " = ";
		node.initializer->accept(*this);
	}
}

void Printer::visit(VarDeclaration& node) {
	std::cout << node.type << " ";
	for (std::size_t i = 0, size = node.declarator_list.size(); i < size; ++i) {
		node.declarator_list[i]->accept(*this);
		if (i != size - 1) {
			std::cout << ", ";
		}
	}
	std::cout << ";";
}

void Printer::visit(ParameterDeclaration& node) {
	std::cout << node.type << " ";
	node.init_declarator->accept(*this);
}

void Printer::visit(FuncDeclaration& node) {
	std::cout << node.type << " ";
	node.declarator->accept(*this);
	std::cout << "(";
	for (std::size_t i = 0, size = node.args.size(); i < size; ++i) {
		node.args[i]->accept(*this);
		if (i != size - 1) {
			std::cout << ", ";
		}
	}
	std::cout << ")";
	node.body->accept(*this);
}

void Printer::visit(CompoundStatement& node) {
	std::cout << " {" << std::endl;
	for (auto& statement : node.statements) {
		statement->accept(*this);
		std::cout << std::endl;
	}
	std::cout << "}";
}

void Printer::visit(DeclarationStatement& node) {
	node.declaration->accept(*this);
}

void Printer::visit(ExpressionStatement& node) {
	node.expression->accept(*this);
	std::cout << ";";
}

void Printer::visit(ConditionalStatement& node) {
	std::cout << "if (";
	node.if_branch.first->accept(*this);
	std::cout << ")";
	node.if_branch.second->accept(*this);
	for (auto& branch : node.elif_branches) {
		std::cout << "elif (";
		branch.first->accept(*this);
		std::cout << ")";
		branch.second->accept(*this);
	}
	if (node.else_branch) {
		std::cout << "else";
		node.else_branch->accept(*this);
	}
}

void Printer::visit(WhileStatement& node) {
	std::cout << "while (";
	node.condition->accept(*this);
	std::cout << ")";
	node.statement->accept(*this);
}

void Printer::visit(ForStatement&) {
	//TBD
}

void Printer::visit(RepeatStatement& node) {
	std::cout << "repeat";
	node.statement->accept(*this);
}

void Printer::visit(ReturnStatement& node) {
	std::cout << "return ";
	node.expression->accept(*this);
	std::cout << ";";
}

void Printer::visit(BreakStatement&) {
	std::cout << "break;";
}

void Printer::visit(ContinueStatement&) {
	std::cout << "continue;";
}

///////////////////////////////////////////////////////////////////

void Printer::visit(BinaryOperation& node) {
	node.lhs->accept(*this);
	std::cout << " " + node.op + " ";
	node.rhs->accept(*this);
}

void Printer::visit(PrefixExpression& node) {
	std::cout << node.op;
	node.base->accept(*this);
}

void Printer::visit(PostfixIncrementExpression& node) {
	node.base->accept(*this);
	std::cout << "++";
}

void Printer::visit(PostfixDecrementExpression& node) {
	node.base->accept(*this);
	std::cout << "--";
}

void Printer::visit(SubscriptExpression& node) {
	node.base->accept(*this);
	std::cout << "[";
	node.index->accept(*this);
	std::cout << "]";
}

void Printer::visit(FunctionCallExpression& node) {
	node.base->accept(*this);
	std::cout << "(";
	for (std::size_t i = 0, size = node.args.size(); i < size; ++i) {
		node.args[i]->accept(*this);
		if (i != size - 1) {
			std::cout << ", ";
		}
	}
	std::cout << ")";
}


void Printer::visit(IdentifierExpression& node) {
	std::cout << node.name;
}

void Printer::visit(IntLiteral& node) {
	std::cout << node.value;
}

void Printer::visit(FloatLiteral& node) {
	std::cout << node.value;
}

void Printer::visit(CharLiteral& node) {
	std::cout << node.value;
}

void Printer::visit(StringLiteral& node) {
	std::cout << node.value;
}

void Printer::visit(BoolLiteral& node) {
	std::cout << (node.value ? "true" : "false");
}

void Printer::visit(ParenthesizedExpression& node) {
	std::cout << "(";
	node.expression->accept(*this);
	std::cout << ")";
}