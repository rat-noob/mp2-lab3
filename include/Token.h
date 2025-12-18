#pragma once
#include <string>
#include <iostream>
#include <cctype>
#include <map>
#include <stack>
#include <queue>

using namespace std;

enum TokenType {
	Number,
	Variable,
	Binary_op,
	Unary_minus,
	Unary_plus,
	Paren_open,
	Paren_close,
	End
};

struct Token {
	TokenType type;
	string value;

	Token(TokenType t = TokenType::End, string val):type(t),value(val){}

};