#pragma once
#include <iostream>
#include "queue.h"
#include "stack.h"
#include "Tokenizer.h"
#include <map>

using namespace std;

class Calc {
public:
	double Calculate(TQueue<char> postfix, map<char, double> operands);
	double Calculate(TQueue<Token>postfix, map<char, double> operands);
};