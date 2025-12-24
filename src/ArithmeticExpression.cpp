#include "ArithmeticExpression.h"

ArithmeticExpression::ArithmeticExpression(string inf) :Sinfix(inf) {

	Tokenizer tokenizer(inf);
	priority = { {"+",1},{"-",1},{"*",2},{"/",2},{"(",0},{"~",3} };
	Qinfix = pars.Parse(Sinfix);
	TokQinfix = tokenizer.getAllTokens();
	if (pars.IsCorrect(Qinfix)) {
		/*postfix = pars.ToPostfix(Qinfix, priority, operands);*/
		TokPostfix = pars.ToPostfix(TokQinfix, priority, operands);
	}
	else exit(-1);


}

void ArithmeticExpression::PrintInfix(void) {
	TQueue<char> temp = this->Qinfix;

	while (!temp.IsEmpty()) {
		cout << temp.pop();
	}
	cout << "\n";

	//почему-то не работает
	/*while (!(Qinfix.IsEmpty())) {
		cout << Qinfix.pop();
	}*/
}
void ArithmeticExpression::PrintPostfix(void) {
	/*TQueue<char> temp = this->postfix;
	while (!temp.IsEmpty()) {
		cout << temp.pop();
	}для старого варианта с чарами
	cout << "\n";*/

	TQueue<Token> temp = this->TokPostfix;
	while (!temp.IsEmpty()) {
		Token t = temp.pop();
		cout << t.value;
	}
	cout << "\n";

}

TQueue<string> ArithmeticExpression::GetOperands() {
	/*TQueue<char> op(15);*/
	TQueue<string> op(15);
	for (const auto& item : operands) {
		/*char it = item.first;*/
		string it = item.first;
		op.push(it);
	}

	return op;
}

double ArithmeticExpression::GetResult(map<string, double> val) {
	/*map<char, double> newop;*/
	map<string, double> newop;
	for (const auto& item : operands) {
		/*char it = item.first;*/
		string it = item.first;
		double v = item.second;
		newop[it] = v;
	}
	for (const auto& item : val) {
		string it = item.first;
		double v = item.second;
		newop[it] = v;
	}



	double res = calc.Calculate(TokPostfix, newop);
	return res;
}


















//ArithmeticExpression::Parse() {
//	for (size_t i = 0; i < Sinfix.length(); i++)
//	{
//		Qinfix.push(Sinfix[i]);
//	}
//}


//ArithmeticExpression::ToPostfix() {
//	TStack<char> st(15);
//	char stackitem;
//	char qitem;
//	while (!Qinfix.IsEmpty()) {
//		qitem = Qinfix.pop();
//		switch (qitem) {
//		case'(':
//			st.push(qitem);
//			break;
//
//		case')':
//			stackitem = st.pop();
//			while (stackitem != '(') {
//				postfix.push(stackitem);
//				stackitem = st.pop();
//			}
//			break;
//		case'+':case'-':case'*':case'/':
//			while (!st.IsEmpty()) {
//				stackitem = st.pop();
//				if (priority[qitem] <= priority[stackitem]) {
//					postfix.push(stackitem);
//				}
//				else {
//					st.push(stackitem);
//					break;
//				}
//			}
//			st.push(qitem);
//			break;
//		default:
//			postfix.push(qitem);
//		}
//	}
//	while (!st.IsEmpty()) {
//		stackitem = st.pop();
//		postfix.push(stackitem);
//	}
//}