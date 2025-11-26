#pragma once
#include <iostream>
#include <map>
#include "MyParser.h"
#include "queue.h"
#include "stack.h"
using namespace std;

class ArithmeticExpression {
	
	string Sinfix;
	TQueue<char> Qinfix;
	TQueue<char> postfix;
	/*TQueue<char> Qinfix(15);
	TQueue<char> postfix(15);*/

	map<char, int> priority;
	map<char, double> operands;

	MyParser pars;

	double result;

public:
	ArithmeticExpression(string infix);

	void PrintInfix();
	void PrintPostfix();

	TQueue<char> GetOperands();
	double GetResult();


	/*void Parse();
	void ToPostfix();
	double Calculate(const map<char, double>& values);*/
};