#pragma once
#include <iostream>

#include "Tree.h"
#include <map>
#include <string>
#include <stdexcept>
#include <cmath>

using namespace std;

class Visitor {
public:
	virtual ~Visitor() = default;

	virtual void visit(const Node* node) = 0;
};

class PrintVisitor:public Visitor {
private:
    bool needParentheses = false;

       int getPriority(TokenType type) const {
           switch (type) {
           case TokenType::Binary_op:
               return 1;
           case TokenType::Unary_minus:
           case TokenType::Unary_plus:
               return 2;
           default:
               return 0;
           }
       }

public:
    void visit(const Node* node) override {
        TokenType type = node->data.type;

        switch (type) {
        case TokenType::Number:
        case TokenType::Variable:
            cout << node->data.value;
            break;

        case TokenType::Unary_minus:
            cout << "-";
            node->left->accept(this);
            break;

        case TokenType::Unary_plus:
            cout << "+";
            node->left->accept(this);
            break;
        case TokenType::Binary_op:
        {
            bool leftNeedParen = node->left &&
                getPriority(node->left->data.type) < getPriority(type);
            bool rightNeedParen = node->right &&
                getPriority(node->right->data.type) < getPriority(type);

            if (leftNeedParen) cout << "(";
            node->left->accept(this);
            if (leftNeedParen) cout << ")";

            cout << " " << node->data.value << " ";

            if (rightNeedParen) cout << "(";
            node->right->accept(this);
            if (rightNeedParen) cout << ")";
        }
        break;

        default:
            break;

        }
    }
};


class CalcVisitor :public Visitor {
private:
    map<string, double> variables;
    double result;
public:
    CalcVisitor(const map<string, double>& vars = {})
        : variables(vars), result(0.0) {
    }

    double getResult() const { return result; }
    
    void visit(const Node* node) override {
        TokenType type = node->data.type;

        switch (type) {
        case TokenType::Number:
            result = stod(node->data.value);
            break;
        case TokenType::Variable:
        {
            auto it = variables.find(node->data.value);
            if (it != variables.end()) {
                result = it->second;
            }
            else {
                throw runtime_error("Unknown variable: " + node->data.value);
            }
        }
        break;
        case TokenType::Binary_op:
        {
            
            node->left->accept(this);
            double leftVal = result;

            
            node->right->accept(this);
            double rightVal = result;

            char op = node->data.value[0];
            switch (op) {
            case '+': result = leftVal + rightVal; break;
            case '-': result = leftVal - rightVal; break;
            case '*': result = leftVal * rightVal; break;
            case '/':
                if (abs(rightVal) < 1e-12) {
                    throw runtime_error("Division by zero");
                }
                result = leftVal / rightVal;
                break;
            default:
                throw runtime_error("Unknown operation: " + string(1, op));
            }
        }
        break;

        case TokenType::Unary_minus:
            node->left->accept(this);
            result = -result;
            break;

        case TokenType::Unary_plus:
            node->left->accept(this);
            break;

        default:
            throw runtime_error("Unknown node type");
        }
    }
};