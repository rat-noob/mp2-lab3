#pragma once
 
//#include <iostream>
//#include <map>
//#include <string>
//#include <cmath>
//using namespace std;
//
//class Visitor;
//
//class Expr {
//public:
//	virtual ~Expr() = default;
//	virtual double accept(Visitor* v) const = 0;
//};
//
//class Numbers : public Expr {
//	double val;
//public:
//	Numbers(double _val): val(_val){}
//	double getVal() const { return val; }
//	double accept(Visitor* v) const override { return v->visitNumber(this); }
//};
//
//class Variables : public Expr {
//	string name;
//
//public:
//	Variables(string _name) : name(_name){}
//	string getName() const { return name; }
//	double accept(Visitor* v) const override { return v->visitVariable(this); }
//};
//
//class BinaryOp : public Expr {
//	char op;
//	Expr* right;
//	Expr* left;
//public:
//	BinaryOp(char _op, Expr* _right, Expr* _left): op(_op), right(_right), left(_left) {}
//	~BinaryOp() { delete left; delete right; }
//	char getOp() const { return op; }
//	Expr* getRight() const { return right; }
//	Expr* getLeft() const { return left; }
//
//	double accept(Visitor* v) const override{ return v->visitBinaryOp(this); }
//};
//
//class UnaryMinus : public Expr {
//	Expr* operand;
//public:
//	UnaryMinus(Expr* _operand): operand(_operand){}
//	~UnaryMinus() { delete operand; }
//
//	Expr* getOperand() const  { return operand; }
//	double accept(Visitor* v) const override { return v->visitUnaryMinus(this); }
//};