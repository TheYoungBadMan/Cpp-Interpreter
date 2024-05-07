#pragma once

#include <iostream>
#include <vector>
#include <memory>

struct Type {
	bool isConst;

	Type(bool isConst) : isConst(isConst) {}
	virtual ~Type() = default;

	virtual void print() const = 0;
	virtual std::shared_ptr<Type> getBaseType() const = 0;
};

struct NonRefType : public Type {
	NonRefType(bool isConst) : Type(isConst) {}
	virtual ~NonRefType() = default;

	virtual void print() const override = 0;
	virtual std::shared_ptr<Type> getBaseType() const override = 0;
};

struct FunctionType : public NonRefType {

	std::shared_ptr<Type> returnType;
	std::vector<std::shared_ptr<Type>> parameterTypes;

	FunctionType(const std::shared_ptr<Type>& returnType, const std::vector<std::shared_ptr<Type>>& parameterTypes)
		: NonRefType(false), returnType(returnType), parameterTypes(parameterTypes) {}

	void print() const override {}

	std::shared_ptr<Type> getBaseType() const override {
		return nullptr;
	}
};

struct BasicType : public NonRefType {
	std::string name;

	BasicType(const std::string& name, bool isConst = false) : name(name), NonRefType(isConst) {}

	void print() const override {
		std::cout << name << " ";
	}

	std::shared_ptr<Type> getBaseType() const override {
		return nullptr;
	}
};

struct IntType : public BasicType {
	IntType(bool isConst = false) : BasicType("", isConst) {}
	void print() const override {
		std::cout << "int ";
	}
	std::shared_ptr<Type> getBaseType() const override {
		return nullptr;
	}

	bool isCompatible(const std::shared_ptr<Type>& other_type) {
		if (std::dynamic_pointer_cast<IntType>(other_type)
		|| std::dynamic_pointer_cast<FloatType>(other_type))
	}
};

struct NonBasicType : public NonRefType {
	std::string name;

	NonBasicType(const std::string& name, bool isConst = false) : name(name), NonRefType(isConst) {}

	void print() const override {
		std::cout << name << " ";
	}

	std::shared_ptr<Type> getBaseType() const override {
		return nullptr;
	}
};

struct PtrType : public NonRefType {
	std::shared_ptr<NonRefType> baseType;

	PtrType(const std::shared_ptr<NonRefType>& baseType, bool isConst = false) : baseType(baseType), NonRefType(isConst) {}

	void print() const override {
		baseType->print();
		std::cout << "* ";
	}

	std::shared_ptr<Type> getBaseType() const override {
		return baseType;
	}
};

struct RefType : public Type {
	std::shared_ptr<NonRefType> baseType;

	RefType(const std::shared_ptr<NonRefType>& baseType, bool isConst = false) : baseType(baseType), Type(isConst) {}

	void print() const override {
		baseType->print();
		std::cout << "& ";
	}

	std::shared_ptr<Type> getBaseType() const override {
		return baseType;
	}
};