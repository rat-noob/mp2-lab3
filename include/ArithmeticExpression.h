#pragma once
#include <iostream>
#include <map>
#include "D:\UNN\c++\lab3\mp2-lab3\include\queue.h"
#include "D:\UNN\c++\lab3\mp2-lab3\include\stack.h"
using namespace std;

class ArithmeticExpression {
	
	TQueue<char> Qinfix(15);
	string Sinfix;
	
	TQueue<char> postfix(15);

	/*TStack<char> lexems(15);*/


	map<char, int> priority;
	map<char, double> operands;

public:
	ArithmeticExpression(string infix);
	
	void Parse();
	void ToPostfix();
	TQueue GetInfix();
	TStack GetPostfix();

	double Calculate(const map<char, double>& values);
};