#pragma once
#include <string>
#include <iostream>
#include <cctype>
#include <map>
#include <stack>
#include <queue>
#include "Token.h"
using namespace std;
class Tokenizer {
	string expression;
	int pos;
	char currentChar;

	void next() {
	}
	string readNumber() {
	}
	string readIdentifier();
public:
	Tokenizer(const string& expr);
	Token getNewToken(bool expectOperand = true);
	TQueue<Token> getAllTokens();
};
