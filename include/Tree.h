#pragma once
#include "Token.h"
#include <memory>
#include "queue.h"
#include "stack.h"
#include <iostream>

class Visitor;

using namespace std;







struct Node {
	Token data;
	Node* left;
	Node* right;

	Node() : left(nullptr), right(nullptr) {}
	Node(const Token& token) : data(token), left(nullptr), right(nullptr) {}
	Node(TokenType type, const string& value = "")
		: data(type, value), left(nullptr), right(nullptr) {
	}


	bool isLeaf() const { return left == nullptr && right == nullptr; }
	bool isNumber() const { return data.type == TokenType::Number; }
	bool isVariable() const { return data.type == TokenType::Variable; }
	bool isBinaryOp() const { return data.type == TokenType::Binary_op; }
	bool isUnaryMinus() const { return data.type == TokenType::Unary_minus; }
	bool isUnaryPlus() const { return data.type == TokenType::Unary_plus; }

	void accept(Visitor* visitor) const;
};

class Tree {
	Node* root;

	void clear(Node* node) {
		if (!node) return;

		clear(node->left);
		clear(node->right);

		delete node;
	}

	Node* copy(Node* node) {
		if (!node) return nullptr;

		Node* newnode = new Node(node->data);
		newnode->left = node->left;
		newnode->right = node->right;
		return newnode;
	}


	//сюда добавить обходы

	void LTR(Node* node, vector<const Node*>& result) const {
		if (!node) return;

		LTR(node->left,result);
		result.push_back(node);
		LTR(node->right,result);
	}

	void TLR(Node* node, vector<const Node*>& result) const {
		if (!node) return;

		result.push_back(node);
		TLR(node->left,result);
		TLR(node->right,result);

	}

	void accept(Node* node, Visitor* visitor) const {
		if (!node) return;

		if (node->isBinaryOp()) {
			accept(node->left, visitor);
			accept(node->right, visitor);
		}
		else if (node->isUnaryMinus() || node->isUnaryPlus()) accept(node->left, visitor);


		visitor->visit(node);
	}




	int height(Node* node) const{
		if (!node) return 0;
		return max(height(node->left), height(node->right)) + 1;
	}

	int size(Node* node) const{
		if (!node) return 0;
		return size(node->left) + size(node->right) + 1;
	}

public:
	Tree(): root(nullptr){}
	
	Tree(Node* node) : root(node) {}
	Tree(const Tree& other) : root(copy(other.root)) {}
	

	~Tree() {
		clear(root);
	}

	Tree& operator=(const Tree& other) {
		if (this != &other) {
			clear(root);
			root = copy(other.root);
		}
		return *this;
	}

	Node* getRoot() const { return root; }
	bool isEmpty() const { return root == nullptr; }

	
	void setRoot(Node* node) { root = node; }

	void accept(Visitor* visitor) const {//дописать в приват секцию
		if (!root) return;
		accept(root, visitor);
	}
	//obxodi

	void TLR(vector<const Node*>& result) const {
		TLR(root, result);
	}
	void LTR(vector<const Node*>& result) const {
		LTR(root, result);
	}
	int height() const {
		return height(root);
	}

	int size() const {
		return size(root);
	}

	static Tree fromPostfix(TQueue<Token>& postfix) {
		stack<Node*> st;

		while (!postfix.IsEmpty()) {
			Token token = postfix.pop();
			Node* newNode = new Node(token);

			switch (token.type) {
			case TokenType::Number:
			case TokenType::Variable:
				st.push(newNode);
				break;
			case TokenType::Binary_op:

				if (st.size() < 2) {
					delete newNode;
					throw runtime_error("не хватает элементов в стеке");
				}
				newNode->right = st.top(); st.pop();
				newNode->left = st.top(); st.pop();

				st.push(newNode);
				break;

			case TokenType::Unary_minus:
			case TokenType::Unary_plus:
				if (st.empty()) {
					delete newNode;
					throw runtime_error("не хватает элементов в стеке");
				}
				newNode->left = st.top(); st.pop();
				st.push(newNode);
				break;

			default:
				delete newNode;
				throw runtime_error("неизвестный тип");

			}
		}

		if (st.size() != 1) {
			throw runtime_error("чето не так");
		}

		return Tree(st.top());


	}
	


};

//inline void Node::accept(Visitor* visitor) const {
//	visitor->visit(this);
//}