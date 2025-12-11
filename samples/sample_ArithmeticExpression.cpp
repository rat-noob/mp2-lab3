#include "ArithmeticExpression.h"
#include <map>

using namespace std;

void main() {
	setlocale(LC_ALL, "Russian");
	string Expr= "(a+b*c)*(c/d-e)";
	string wrong1 = "a+b";
	string wr = "a+b)";
	ArithmeticExpression example(Expr);
	example.PrintInfix();
	example.PrintPostfix();
	
	
	map<char, double> values;
	double val;
	TQueue<char> op = example.GetOperands();

	while (!op.IsEmpty()) {
		char elem = op.pop();
		cout << "¬ведите значение " << elem<<": ";
		cin >> val;
		values[elem] = val;
	}

	cout << example.GetResult(values);

}