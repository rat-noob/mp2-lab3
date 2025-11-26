#pragma once
#include "queue.h"
#include "stack.h"
#include <map>
class MyParser {
public:
	bool IsCorrect(TQueue<char> Qinfix);
	TQueue<char> Parse(string Sinfix);
	TQueue<char> ToPostfix(TQueue<char> Qinfix, map<char, int> priority, map<char, double> &operands);

};