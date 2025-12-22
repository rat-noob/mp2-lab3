#pragma once
#include <iostream>
#include <map>
#include "MyParser.h"
#include "queue.h"
#include "stack.h"
#include "Calc.h"
#include "Token.h"
#include "Tokenizer.h"
using namespace std;

class ArithmeticExpression {
	
	string Sinfix;
	TQueue<char> Qinfix;
	TQueue<char> postfix;
	TQueue<Token> TokQinfix;//для нового варианта
	TQueue<Token> TokPostfix;//для нового варианта
	/*TQueue<char> Qinfix(15);
	TQueue<char> postfix(15);*/

	/*map<char, int> priority;*/
	map<string, int> priority;
	/*map<char, double> operands;*/
	map<string, double> operands;

	MyParser pars;
	Calc calc;
	Tokenizer* tok;

	double result;

public:
	ArithmeticExpression(string infix);

	void PrintInfix();
	void PrintPostfix();

	TQueue<string> GetOperands();
	double GetResult(map<string, double> val);


	/*void Parse();
	void ToPostfix();
	double Calculate(const map<char, double>& values);*/
};