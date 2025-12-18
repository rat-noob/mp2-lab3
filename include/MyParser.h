#pragma once
#include "queue.h"
#include "stack.h"
#include <map>
#include "Token.h"
#include "Tokenizer.h"
class MyParser {
public:
	bool IsCorrect(TQueue<char> Qinfix);
	TQueue<char> Parse(string Sinfix);
	TQueue<char> ToPostfix(TQueue<char> Qinfix, map<string, int> priority, map<char, double> &operands);
	TQueue<Token> ToPostfix(TQueue<Token> Qinfix, map<string, int> priority, map<char, double>& operands);
};