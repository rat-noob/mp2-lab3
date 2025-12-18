#include "Tokenizer.h"


void Tokenizer::next() {
	if (pos < expression.length()) currentChar = expression[pos++];
	else currentChar = '\0';
}
string Tokenizer::readNumber(){
	string result;
	bool hasDecimal = false;
	while (currentChar != '\0' && (isdigit(currentChar) || currentChar=='.') {
		if (currentChar == '.') {
			if (hasDecimal) return -1;
			hasDecimal = true;
		}
		result += currentChar;
		next();
	}
	return result;
}
string Tokenizer::readIdentifier() {
	string result;
	while (currentChar != '\0' && isalnum(currentChar)) {
		result += currentChar;
		next();
	}
	return result;
}
Tokenizer::Tokenizer(const string& expr) :expression(expr), pos(0) {
	next();
}
Token Tokenizer::getNewToken(bool expectOperand  = true) {
	int cur = pos - 1;
	
	if(currentChar=='\0') return Token(TokenType::End, "");
	if (isdigit(currentChar)) {
		string number = readNumber();
		return Token(TokenType::Number, number);
	}
	if (isalpha(currentChar)) {
		string id = readIdentifier();
		return Token(TokenType::Variable, id);
	}
	if (currentChar == '(') {
		string c = currentChar;
		next();
		return Token(TokenType::Paren_open, c);
	}
	if (currentChar == ')') {
		string c = currentChar;
		next();
		return Token(TokenType::Paren_close, c);
	}
	if (currentChar == '+' || currentChar == '-') {
		string op = currentChar;

		if (expectOperand) {
			next();
			if (op == '+') return Token(TokenType::Unary_plus, op);
			else return Token(TokenType::Unary_minus, op);
		}
		else {
			next();
			return Token(TokenType::Binary_op, op);
		}
	}

	if (currentChar == '*' || currentChar == '/') {
		string op = currentChar;
		next();
		return Token(TokenType::Binary_op, op);
	}
	throw - 1;
}
TQueue<Token> Tokenizer::getAllTokens() {
	TQueue<Token> tokens;
	bool expectOperand = true;

	char savedch = currentChar;
	int savedpos = pos;

	pos = 0;
	next();

	try {
		while (true) {
			Token token = getNewToken(expectOperand);
			if (token.type == TokenType::End) break;

			tokens.push(token);

			switch (token) {
			case TokenType::Variable:
			case TokenType::Number:
			case TokenType::Paren_close:
				expectOperand = false;
				break;
			case TokenType::Paren_open:
			case TokenType::Binary_op:
			case TokenType::Unary_minus:
			case TokenType::Unary_plus:
				expectOperand = true;
				break;
			default:
				expectOperand = false;
			}
		}
		}
	catch (...) {
		pos = savedpos;
		currentChar = savedch;
		throw;
		}
	pos = savedpos;
	currentChar = savedch;

	return tokens;
	}
	