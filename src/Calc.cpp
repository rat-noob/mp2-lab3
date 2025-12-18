#include "Calc.h"

double Calc::Calculate(TQueue<char> postfix, map<char, double> operands) {
	TStack<double> st;
	double lo, ro;//лувый и правый операнды
	while (!postfix.IsEmpty()) {
		switch (char elem = postfix.pop()) {
		case '+':
			ro = st.pop();
			lo = st.pop();
			st.push(lo + ro);
			break;
		case '-':
			ro = st.pop();
			lo = st.pop();
			st.push(lo - ro);
			break;
		case '*':
			ro = st.pop();
			lo = st.pop();
			st.push(lo* ro);
			break;
		case '/':
			ro = st.pop();
			lo = st.pop();
			st.push(lo / ro);
			break;
		default:
			st.push(operands[elem]);
		}
	}
		
	
	return st.pop();
}

double Calc::Calculate(TQueue<Token>postfix, map<string, double> operands) {//поменял с чар на стринг
	TStack<double> st;
	double lo, ro;
	Token cur;


	while (!postfix.IsEmpty()) {
		cur = postfix.pop();
		switch (cur.type) {
		case Number:
			st.push(stod(cur.value));
			break;
		case Binary_op:
			ro = st.pop();
			lo = st.pop();
			switch (cur.value) {
			case "+":
				st.push(lo + ro);
				break;
			case"-":
				st.push(lo - ro);
				break;
			case "*":
				st.push(lo * ro);
				break;
			case "/":
				if (ro == 0) throw - 1;
				st.push(lo / ro);
				break;
			}
			break;
		case Unary_minus:
			double val = st.pop();
			st.push(-val);
			break;
		case Variable:
			double val = operands.find(cur.value);
			st.push(val->second);
			break;
		default:
			throw-1

		}
	}

}