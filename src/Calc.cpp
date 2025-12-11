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