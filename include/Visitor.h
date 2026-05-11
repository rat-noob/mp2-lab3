#pragma once
#include <iostream>

//#include "Tree.h"
#include <map>
#include <string>
#include <stdexcept>
#include <cmath>

using namespace std;
class Visitor;
//class Numbers;
//class Variables;
//class BinaryOp;
//class UnaryMinus;
// 
// 
//¬€–¿∆≈Õ»ﬂ
class Expr {
public:
	virtual ~Expr() = default;
	virtual double accept(Visitor* v) const = 0;
};

class Numbers : public Expr {
	double val;
public:
	Numbers(double _val) : val(_val) {}
	double getVal() const { return val; }
	double accept(Visitor* v) const override { return v->visitNumber(this); }
};

class Variables : public Expr {
	string name;

public:
	Variables(string _name) : name(_name) {}
	string getName() const { return name; }
	double accept(Visitor* v) const override { return v->visitVariable(this); }
};

class BinaryOp : public Expr {
	char op;
	Expr* right;
	Expr* left;
public:
	BinaryOp(char _op, Expr* _right, Expr* _left) : op(_op), right(_right), left(_left) {}
	~BinaryOp() { delete left; delete right; }
	char getOp() const { return op; }
	Expr* getRight() const { return right; }
	Expr* getLeft() const { return left; }

	double accept(Visitor* v) const override { return v->visitBinaryOp(this); }
};

class UnaryMinus : public Expr {
	Expr* operand;
public:
	UnaryMinus(Expr* _operand) : operand(_operand) {}
	~UnaryMinus() { delete operand; }

	Expr* getOperand() const { return operand; }
	double accept(Visitor* v) const override { return v->visitUnaryMinus(this); }
};



//¬»«»“Œ–€




class Visitor {
public:
    virtual ~Visitor() = default;
    virtual double visitNumber(const Numbers* num) = 0;
    virtual double visitVariable(const Variables* var) = 0;
    virtual double visitBinaryOp(const BinaryOp* op) = 0;
    virtual double visitUnaryMinus(const UnaryMinus* op) = 0;
};

class CalcVisitor :public Visitor {
    map<string, double> variables;
public:
    CalcVisitor(const map<string, double>& vars = {}) :variables(vars) {}
    double visitNumber(const Numbers* num) override{
        return num->getVal();
    }
	double visitVariable(const Variables* var) override{
		auto it = variables.find(var->getName());
		if (it != variables.end()) return it->second;
		throw std::runtime_error("Unknown variable: " + var->getName());
	}
	double visitBinaryOp(const BinaryOp* op) override{
		double left = op->getLeft()->accept(this);
		double right = op->getRight()->accept(this);
		switch (op->getOp()) {
		case '+': return left + right;
		case '-': return left - right;
		case '*': return left * right;
		case '/': if (right == 0) throw std::runtime_error("Division by zero");
			return left / right;
		default:
			throw std::runtime_error("Unknown operator");
		}
	}
	double visitUnaryMinus(const UnaryMinus* op) override {
		return -op->getOperand()->accept(this);
	}
};
class printVisitor : public Visitor {
public:
	double visitNumber(const Numbers* num) override {
		cout << num->getVal(); return 0;
	}
	double visitVariable(const Variables* var) override {
		cout << var->getName(); return 0;
	}
	double visitBinaryOp(const BinaryOp* op) override {
		cout << "(";
		op->getLeft()->accept(this);
		cout << op->getOp();
		op->getRight()->accept(this);
		cout << ")";
		return 0;
	}
	double visitUnaryMinus(const UnaryMinus* op) override {
		cout << "-(";
		op->getOperand()->accept(this);
		cout << ")";
		return 0;
	}
};



///ƒÀﬂ ”ƒŒ¡ÕŒ√Œ —Œ«ƒ¿Õ»ﬂ

Expr* num(double val) {
	return new Numbers(val);
}

Expr* var(const std::string& name) {
	return new Variables(name);
}

Expr* add(Expr* left, Expr* right) {
	return new BinaryOp('+', left, right);
}

Expr* sub(Expr* left, Expr* right) {
	return new BinaryOp('-', left, right);
}

Expr* mul(Expr* left, Expr* right) {
	return new BinaryOp('*', left, right);
}

Expr* div(Expr* left, Expr* right) {
	return new BinaryOp('/', left, right);
}

Expr* neg(Expr* operand) {
	return new UnaryMinus(operand);
}







//class Visitor {
//public:
//	virtual ~Visitor() = default;
//
//	virtual void visit(const Node* node) = 0;
//};
//
//class PrintVisitor:public Visitor {
//private:
//    bool needParentheses = false;
//
//       int getPriority(TokenType type) const {
//           switch (type) {
//           case TokenType::Binary_op:
//               return 1;
//           case TokenType::Unary_minus:
//           case TokenType::Unary_plus:
//               return 2;
//           default:
//               return 0;
//           }
//       }
//
//public:
//    void visit(const Node* node) override {
//        TokenType type = node->data.type;
//
//        switch (type) {
//        case TokenType::Number:
//        case TokenType::Variable:
//            cout << node->data.value;
//            break;
//
//        case TokenType::Unary_minus:
//            cout << "-";
//            node->left->accept(this);
//            break;
//
//        case TokenType::Unary_plus:
//            cout << "+";
//            node->left->accept(this);
//            break;
//        case TokenType::Binary_op:
//        {
//            bool leftNeedParen = node->left &&
//                getPriority(node->left->data.type) < getPriority(type);
//            bool rightNeedParen = node->right &&
//                getPriority(node->right->data.type) < getPriority(type);
//
//            if (leftNeedParen) cout << "(";
//            node->left->accept(this);
//            if (leftNeedParen) cout << ")";
//
//            cout << " " << node->data.value << " ";
//
//            if (rightNeedParen) cout << "(";
//            node->right->accept(this);
//            if (rightNeedParen) cout << ")";
//        }
//        break;
//
//        default:
//            break;
//
//        }
//    }
//};
//
//
//class CalcVisitor :public Visitor {
//private:
//    map<string, double> variables;
//    double result;
//public:
//    CalcVisitor(const map<string, double>& vars = {})
//        : variables(vars), result(0.0) {
//    }
//
//    double getResult() const { return result; }
//    
//    void visit(const Node* node) override {
//        TokenType type = node->data.type;
//
//        switch (type) {
//        case TokenType::Number:
//            result = stod(node->data.value);
//            break;
//        case TokenType::Variable:
//        {
//            auto it = variables.find(node->data.value);
//            if (it != variables.end()) {
//                result = it->second;
//            }
//            else {
//                throw runtime_error("Unknown variable: " + node->data.value);
//            }
//        }
//        break;
//        case TokenType::Binary_op:
//        {
//            
//            node->left->accept(this);
//            double leftVal = result;
//
//            
//            node->right->accept(this);
//            double rightVal = result;
//
//            char op = node->data.value[0];
//            switch (op) {
//            case '+': result = leftVal + rightVal; break;
//            case '-': result = leftVal - rightVal; break;
//            case '*': result = leftVal * rightVal; break;
//            case '/':
//                if (abs(rightVal) < 1e-12) {
//                    throw runtime_error("Division by zero");
//                }
//                result = leftVal / rightVal;
//                break;
//            default:
//                throw runtime_error("Unknown operation: " + string(1, op));
//            }
//        }
//        break;
//
//        case TokenType::Unary_minus:
//            node->left->accept(this);
//            result = -result;
//            break;
//
//        case TokenType::Unary_plus:
//            node->left->accept(this);
//            break;
//
//        default:
//            throw runtime_error("Unknown node type");
//        }
//    }
//};