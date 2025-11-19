#include "ArithmeticExpression.h"

ArithmeticExpression::ArithmeticExpression(string inf):Sinfix(inf) {
	
	
	priority = { {'+',1},{'-',1},{'*',2},{'/',2},{'(',0} };
	ToPostfix();
	Parse();
}
ArithmeticExpression::Parse() {
	for (size_t i = 0; i < inf.length(); i++)
	{
		Qinfix.push(inf[i]);
	}
}
ArithmeticExpression::ToPostfix() {
	TStack<char> st(15);
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
			postfix.push(qitem);
		}
	}
	while (!st.IsEmpty()) {
		stackitem = st.pop();
		postfix.push(stackitem);
	}
}