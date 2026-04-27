#include "ArithmeticExpression.h"

ArithmeticExpression::ArithmeticExpression(string inf) :Sinfix(inf) {

	Tokenizer tokenizer(inf);
	priority = { {"+",1},{"-",1},{"*",2},{"/",2},{"(",0},{"~",3} };
	Qinfix = pars.Parse(Sinfix);
	TokQinfix = tokenizer.getAllTokens();
	if (pars.IsCorrect(Qinfix)) {
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

	
}
void ArithmeticExpression::PrintPostfix(void) {

	TQueue<Token> temp = this->TokPostfix;
	while (!temp.IsEmpty()) {
		Token t = temp.pop();
		cout << t.value;
	}
	cout << "\n";

}

TQueue<string> ArithmeticExpression::GetOperands() {
	
	TQueue<string> op(15);
	for (const auto& item : operands) {
		string it = item.first;
		op.push(it);
	}

	return op;
}

double ArithmeticExpression::GetResult(map<string, double> val) {
	map<string, double> newop;
	for (const auto& item : operands) {
		string it = item.first;
		double v = item.second;
		newop[it] = v;
	}
	for (const auto& item : val) {
		string it = item.first;
		double v = item.second;
		newop[it] = v;
	}
	//new

	Tree tr = Tree::fromPostfix(TokPostfix);
	PrintVisitor printer;
	cout << "Инфиксная запись: ";
	tr.accept(&printer);
	cout << endl;


	CalcVisitor calculator(newop);
	tr.accept(&calculator);
	cout << "Результат: " << calculator.getResult() << endl;

	//

	double res = calculator.getResult();
	//double res = calc.Calculate(TokPostfix, newop);

	return res;
}
