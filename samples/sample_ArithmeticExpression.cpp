#include "ArithmeticExpression.h"
#include <map>

using namespace std;

void main() {
	setlocale(LC_ALL, "Russian");
	string Expr= "(a+b*c)*(c/d-e)";
	string wrong1 = "a1+b2";
	string wr = "-(-1)";
	ArithmeticExpression example(wrong1);
	example.PrintInfix();
	example.PrintPostfix();
	
	
	map<string, double> values;
	double val;
	TQueue<string> op = example.GetOperands();

	while (!op.IsEmpty()) {
		string elem = op.pop();
		cout << "¬ведите значение " << elem<<": ";
		cin >> val;
		values[elem] = val;
	}

	cout << example.GetResult(values);

}