#include "ArithmeticExpression.h"
#include <map>
#include <iomanip>

using namespace std;

void main() {
	setlocale(LC_ALL, "Russian");
	string Expr= "(a+b*c)*(c/d-e)";
	string Expr2 = "2,5+3";
	string wrong1 = "a1+b2";
	string wr = "-(-1)";
	ArithmeticExpression example("x+5");
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
	double result = example.GetResult(values);
	cout  << result;

}