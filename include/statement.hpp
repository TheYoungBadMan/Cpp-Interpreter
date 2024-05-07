#pragma once

#include <string>
#include <vector>
#include <memory>

#include "ast.hpp"

struct VarDeclaration;

using StatementSeq = std::vector<std::shared_ptr<Statement>>;

struct CompoundStatement: public Statement {
	StatementSeq statements;

	CompoundStatement(const StatementSeq&);
	void accept(Visitor&) override;
};

struct ConditionalStatement: public Statement {
	std::pair<std::shared_ptr<Expression>, std::shared_ptr<Statement>> if_branch;
	std::vector<std::pair<std::shared_ptr<Expression>, std::shared_ptr<Statement>>> elif_branches;
	std::shared_ptr<Statement> else_branch;

	ConditionalStatement(
		const std::pair<std::shared_ptr<Expression>, std::shared_ptr<Statement>>&,
		const std::vector<std::pair<std::shared_ptr<Expression>, std::shared_ptr<Statement>>>&,
		const std::shared_ptr<Statement>&
	);
	void accept(Visitor&) override;
};

struct LoopStatement: public Statement {
	virtual ~LoopStatement() = default;
	virtual void accept(Visitor&) override = 0;
};

struct WhileStatement: public LoopStatement {
	std::shared_ptr<Expression> condition;
	std::shared_ptr<Statement> statement;

	WhileStatement(
		const std::shared_ptr<Expression>&,
		const std::shared_ptr<Statement>&
	);
	void accept(Visitor&) override;
};

struct RepeatStatement: public LoopStatement {
	std::shared_ptr<Statement> statement;

	RepeatStatement(const std::shared_ptr<Statement>&);
	void accept(Visitor&) override;
};

struct ForStatement: public LoopStatement {
	void accept(Visitor&) override;
};

struct JumpStatement: public Statement {
	virtual ~JumpStatement() = default;
	virtual void accept(Visitor&) override = 0;
};

struct ReturnStatement: public JumpStatement {
	std::shared_ptr<Expression> expression;

	ReturnStatement(const std::shared_ptr<Expression>&);
	void accept(Visitor&) override;
};

struct BreakStatement: public JumpStatement {
	void accept(Visitor&) override;
};

struct ContinueStatement: public JumpStatement {
	void accept(Visitor&) override;
};

struct DeclarationStatement: public Statement {
	std::shared_ptr<VarDeclaration> declaration;

	DeclarationStatement(const std::shared_ptr<VarDeclaration>&);
	void accept(Visitor&) override;
};

struct ExpressionStatement: public Statement {
	std::shared_ptr<Expression> expression;

	ExpressionStatement(const std::shared_ptr<Expression>&);
	void accept(Visitor&) override;
};