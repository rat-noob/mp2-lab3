#pragma once
#include "Token.h"
#include <memory>
#include "queue.h"
#include "stack.h"
#include <iostream>


using namespace std;

template<class T>
struct Node {
	T data;
	Node* left;
	Node* right;
	int height;

	Node() : left(nullptr), right(nullptr),height(1) {}
	Node(const T& _data) : data(_data), left(nullptr), right(nullptr),height(1) {}
};
template<class T>
class Tree {
protected:
	Node<T>* root;

	virtual void clear(Node<T>* node) {
		if (!node) return;

		clear(node->left);
		clear(node->right);

		delete node;
	}

	virtual Node* copy(Node<T>* node) {
		if (!node) return nullptr;

		Node<T>* newnode = new Node<T>(node->data);
		newnode->left = copy(node->left);
		newnode->right = copy(node->right);
		return newnode;
	}


	//сюда добавить обходы

	virtual void LTR(Node<T>* node, vector<const Node<T>*>& result) const {
		if (!node) return;

		LTR(node->left,result);
		result.push_back(node);
		LTR(node->right,result);
	}

	virtual void TLR(Node<T>* node, vector<const Node<T>*>& result) const {
		if (!node) return;

		result.push_back(node);
		TLR(node->left,result);
		TLR(node->right,result);

	}


	virtual int height(Node<T>* node) const{
		if (!node) return 0;
		return max(height(node->left), height(node->right)) + 1;
	}

	virtual int size(Node<T>* node) const{
		if (!node) return 0;
		return size(node->left) + size(node->right) + 1;
	}

public:
	Tree(): root(nullptr){}
	
	Tree(Node<T>* node) : root(node) {}
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

	Node<T>* getRoot() const { return root; }
	bool isEmpty() const { return root == nullptr; }

	
	void setRoot(Node<T>* node) { root = node; }

	//obxodi

	virtual void TLR(vector<const Node<T>*>& result) const {
		TLR(root, result);
	}
	virtual void LTR(vector<const Node<T>*>& result) const {
		LTR(root, result);
	}
	virtual int height() const {
		return height(root);
	}

	virtual int size() const {
		return size(root);
	}
};


template<class T>
class BST :public Tree<T> {
	
protected:
	using Tree<T>::root;
	Node<T>* insertVal(Node<T>* node, const T& value) {
		if (!node) node = new Node<T>(value);
		Node<T>* t = node;
		while (1) {
			if (t.val == value) throw - 1;
			if (t.val > value) {
				if (t->left == nullptr) {
					t->left = new Node<T>(value);
					return;
				}
				t = t->left;
			}
			else {
				if (t->right == nullptr) {
					t->right = new Node<T>(value);
					return;
				}
				t = t->right;
			}
		}
	}
	bool find(Node<T>* node, const T& value) const{
		if (node == nullptr) return false;
		Node<T>* t = node;
		while (t != nullptr) {
			if (t->data == value) return true;
			if (t->data < value) t = t->right;
			else t = t->left;
		}
		return false;
	}
	Node<T>* findMin(Node<T>* node) const {
		if (node == nullptr) return nullptr;
		Node<T>* t = node;
		while (t != nullptr) {
			t = t->left;
		}
		return t->data;
	}
	Node<T>* findMax(Node<T>* node) const {
		if (node == nullptr) return nullptr;
		Node<T>* t = node;
		while (t != nullptr) {
			t = t->right;
		}
		return t->data;
	}
	bool remove(const T& value) {
		if (!root) return false;

		Node<T>* t = root;
		stack<Node<T>*> path;  

		
		while (t) {
			if (t->data == value) break;
			path.push(t);
			if (t->data > value) t = t->left;
			else t = t->right;
		}

		if (!t) return false;  

		
		if (t->left && t->right) {
			
			Node<T>* successor = t->left;
			while (successor->right) {
				path.push(successor);
				successor = successor->right;
			}

			
			t->data = successor->data;

			Node<T>* parent = path.empty() ? nullptr : path.top();
			if (!path.empty()) path.pop();

			if (parent && parent->left == successor) {
				parent->left = successor->left;
			}
			else if (parent && parent->right == successor) {
				parent->right = successor->left;
			}
			else {
				t->left = successor->left;
			}

			delete successor;
		}
		else {
			Node<T>* child = t->left ? t->left : t->right;

			if (path.empty()) {
				
				root = child;
			}
			else {
				Node<T>* parent = path.top();
				if (parent->left == t) parent->left = child;
				else parent->right = child;
			}

			delete t;
		}

		return true;
	}
	public:
		BST() : Tree<T>() {}
		void insert(const T& value) {
			root = insertVal(root, value);
		}
		bool contains(const T& value) const {
			return find(root, value);
		}
		T getMin() const {
			Node<T>* minNode = findMin(root);
			if (!minNode) throw std::runtime_error("Tree is empty");
			return minNode->data;
		}
		T getMax() const {
			Node<T>* maxNode = findMax(root);
			if (!maxNode) throw std::runtime_error("Tree is empty");
			return maxNode->data;
		}
};
template<class T>
class  AVL :public BST<T> {

	using BST<T>::root;
	using BST<T>::insertVal;
	using BST<T>::remove;

	int getHeight(Node<T>* node) const {
		if (!node) return 0;
		return node->height;
	}
	void updHeight(Node<T>* node) const {
		if (node) {
			node->height = 1 + max(getHeight(node->right), getHeight(node->left));
		}
	}
	int getBalance(Node<T>* node) const {
		if (!node) return 0;
		return getHeight(node->right) - getHeight(node->left);
	}

	Node<T>* rotateRight(Node<T>* node) {
		Node<T>* x = node->left;
		Node<T>* y = x->right;

		x->right = node;
		node->left = y;

		updHeight(node);
		updHeight(x);

		return x;
	}

	Node<T>* rotateLeft(Node<T>* node) {
		Node<T>* x = node->right;
		Node<T>* y = x->left;

		x->left = node;
		node->right = y;

		updHeight(node);
		updHeight(x);

		return x;
	}

	Node<T>* balance(Node<T>* node) {
		if (!node) return nullptr;

		updHeight(node);

		int b = getBalance(node);
		//LL
		if (b < -1 && getBalance(node->left) <= 0) {
			return rotateRight(node);
		}
		//LR
		if (b < -1 && getBalance(node->left)>0) {
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
		//RR
		if (b > 1 && getBalance(node->right) >= 0) {
			return rotateLeft(node);
		}
		//RL
		if (b > 1 && getBalance(node->right < 0)) {
			node->right = rotateRight(node->right);
			return rotateRight(node->right);
		}

		return node;
	}

	Node<T>* insertAVL(Node<T>* node, const T& val) {
		if (!node) return new Node<T>*(val);

		if (val < node->data) {
			node->left = insertAVL(node->left, val);
		}else if(val > node->data) {
			node.right = insertAVL(node->right, val);
		}
		else {
			return node;
		}

		return balance(node);
	}

	Node<T>* removeAVL(Node<T>* node, const T& val,bool& removed) {
		if (!node) return nullptr;

		if (value < node->data) {
			node->left = removeAVL(node->left, value, removed);
		}
		else if (value > node->data) {
			node->right = removeAVL(node->right, value, removed);
		}
		else {
			
			removed = true;

			if (!node->left && !node->right) {
				delete node;
				return nullptr;
			}
			else if (!node->left) {
				Node<T>* temp = node->right;
				delete node;
				return temp;
			}
			else if (!node->right) {
				Node<T>* temp = node->left;
				delete node;
				return temp;
			}
			else {
				Node<T>* minNode = node->right;
				while (minNode->left) minNode = minNode->left;
				node->data = minNode->data;
				node->right = removeAVL(node->right, minNode->data, removed);
			}
		}

		updateHeight(node);
		return balance(node);
	}
};




//static Tree fromPostfix(TQueue<Token>& postfix) {
//	stack<Node*> st;
//
//	while (!postfix.IsEmpty()) {
//		Token token = postfix.pop();
//		Node* newNode = new Node(token);
//
//		switch (token.type) {
//		case TokenType::Number:
//		case TokenType::Variable:
//			st.push(newNode);
//			break;
//		case TokenType::Binary_op:
//
//			if (st.size() < 2) {
//				delete newNode;
//				throw runtime_error("не хватает элементов в стеке");
//			}
//			newNode->right = st.top(); st.pop();
//			newNode->left = st.top(); st.pop();
//
//			st.push(newNode);
//			break;
//
//		case TokenType::Unary_minus:
//		case TokenType::Unary_plus:
//			if (st.empty()) {
//				delete newNode;
//				throw runtime_error("не хватает элементов в стеке");
//			}
//			newNode->left = st.top(); st.pop();
//			st.push(newNode);
//			break;
//
//		default:
//			delete newNode;
//			throw runtime_error("неизвестный тип");
//
//		}
//	}
//
//	if (st.size() != 1) {
//		throw runtime_error("чето не так");
//	}
//
//	return Tree(st.top());
//
//
//}