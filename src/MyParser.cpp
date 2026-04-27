#include "MyParser.h"
#include <cctype>

TQueue<char> MyParser::Parse( string Sinfix) {
	TQueue<char> Qinfix(30);
	for (size_t i = 0; i < Sinfix.length(); i++)
	{
		Qinfix.push(Sinfix[i]);
	}
	return Qinfix;
}

bool MyParser::IsCorrect(TQueue<char> Qinfix) {
	TStack<int> st(15);
	char qitem;
	bool Error=false;
	int i = 0;
	
	while (!Qinfix.IsEmpty()) {
		qitem = Qinfix.pop();
		if (qitem == '(') st.push(i);
		else if (qitem == ')') {
			if (st.IsEmpty()) {
				cout << "Ћишн€€ ')' на позиции " << i << endl;
				return false;
			} 
			else { st.pop(); }
		}
		i++;
	}
	if (!st.IsEmpty()) {
		Error = true;
		while (!st.IsEmpty()) {
			cout <<"Ќ≈закрыта€ скобка на позиции " << st.pop() << " ";
		}
	}
	return !Error;
}




TQueue<Token> MyParser::ToPostfix(TQueue<Token> Qinfix, map<string, int> priority, map<string, double>& operands) {
	TStack<Token> st(100);
	TQueue<Token> postfix(200);
	Token stackitem;
	Token qitem;
	while (!Qinfix.IsEmpty()) {
		qitem = Qinfix.pop();
		switch (qitem.type) {
		case TokenType::Number:
			postfix.push(qitem);
			break;
		case TokenType::Variable:
			if (operands.find(qitem.value) == operands.end()) {
				operands[qitem.value] = 0.0; 
			}
			postfix.push(qitem);
			break;
		case TokenType::Unary_minus:
			postfix.push(Token(TokenType::Number, "0"));
			st.push(qitem);
			break;
		case TokenType::Unary_plus:
			break;
		case TokenType::Paren_open:
			st.push(qitem);
			break;
		case TokenType::Paren_close:
			stackitem = st.pop();
			while (!st.IsEmpty() && stackitem.type != Paren_open) {
				postfix.push(stackitem);
				stackitem = st.pop();
			}
			break;
			
		case TokenType::Binary_op:
			while (!st.IsEmpty()) {
				stackitem = st.top();
				if ((priority[qitem.value] <= priority[stackitem.value])) {
					postfix.push(stackitem);
					st.pop();
					
				}
				else {
					break;
				}
			}
			st.push(qitem);
			break;
		default:
			throw - 1;
		}
	}
	while (!st.IsEmpty()) {
		postfix.push(st.pop());
	}
	return postfix;
}