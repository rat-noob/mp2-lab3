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

//TQueue<char> MyParser::ToPostfix(TQueue<char> Qinfix, map<string, int> priority, map<char,double>& operands) {
//	TStack<char> st(50);
//	TQueue<char> postfix(50);
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
//			while (stackitem != '(' && !st.IsEmpty()) {//если что убрать условие после и
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
//			if (isdigit(qitem)) {
//				operands[qitem] = qitem - '0.0';
//			}
//			else operands.insert({ qitem,0.0 });
//			postfix.push(qitem);
//		}
//	}
//	while (!st.IsEmpty()) {
//		stackitem = st.pop();
//		postfix.push(stackitem);
//	}
//	return postfix;
//}


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
			if (operands.find(qitem.value) == operands.end()) {//возможно удалить
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
			if (!st.IsEmpty()) st.pop();
			break;
		case TokenType::Binary_op://здесь может быть что-то не так
			while (!st.IsEmpty()) {
				stackitem = st.pop();
				/*stackitem = st.top();*/
				if ((priority[qitem.value] <= priority[stackitem.value])&&stackitem.type!=Paren_open) {
					postfix.push(stackitem);
				}
				else {
					st.push(qitem);
					break;
				}
			}
			st.push(qitem);//возможно убрать
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