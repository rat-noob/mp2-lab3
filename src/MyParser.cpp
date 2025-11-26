#include "MyParser.h"

TQueue<char> MyParser::Parse( string Sinfix) {
	TQueue<char> Qinfix(15);
	for (size_t i = 0; i < Sinfix.length(); i++)
	{
		Qinfix.push(Sinfix[i]);
	}
	return Qinfix;
}

bool MyParser::IsCorrect(TQueue<char> Qinfix) {
	TStack<char> st(15);
	char qitem;
	while (!Qinfix.IsEmpty()) {
		qitem = Qinfix.pop();
		if (qitem == '(') st.push('(');
		else if (qitem == ')') {
			if (st.IsEmpty()) return false;
			st.pop();
		} 
	}
	return st.IsEmpty();
}

TQueue<char> MyParser::ToPostfix(TQueue<char> Qinfix, map<char, int> priority, map<char,double>& operands) {
	TStack<char> st(15);
	TQueue<char> postfix(15);
	char stackitem;
	char qitem;
	while (!Qinfix.IsEmpty()) {
		qitem = Qinfix.pop();
		switch (qitem) {
		case'(':
			st.push(qitem);
			break;

		case')':
			stackitem = st.pop();
			while (stackitem != '(') {
				postfix.push(stackitem);
				stackitem = st.pop();
			}
			break;
		case'+':case'-':case'*':case'/':
			while (!st.IsEmpty()) {
				stackitem = st.pop();
				if (priority[qitem] <= priority[stackitem]) {
					postfix.push(stackitem);
				}
				else {
					st.push(stackitem);
					break;
				}
			}
			st.push(qitem);
			break;
		default:
			operands.insert({ qitem,0.0 });
			postfix.push(qitem);
		}
	}
	while (!st.IsEmpty()) {
		stackitem = st.pop();
		postfix.push(stackitem);
	}
	return postfix;
}