#pragma once
#include <iostream>

using namespace std;

template <class T>

class TStack {
	int curr; //текущий элемент
	int n; //макс число элементов
	T* mem;

public:
	TStack(int sz = 20) {
		curr = -1;
		n = sz;
		
		mem = new T[n];
	}

	TStack(const TStack& st) {
		curr = st.curr;
		n = st.n;
		mem = new T[n];

		for (size_t i = 0; i < curr+1; i++)
		{
			mem[i] = st.mem[i];
		}
	}

	~TStack() {
		delete[] mem;
	}

	TStack& operator=(const TStack& st) {
		
		if (this == &st) return *this;
		curr = st.curr;
		n = st.n;

		delete[] mem;

		mem = new T[n];

		for (size_t i = 0; i < curr+1; i++)
		{
			mem[i] = st.mem[i];
		}

		return *this;

	}

	void push(const T& v) {
		if (curr == n - 1) throw out_of_range("stack is full");
		
		curr++;
		mem[curr] = v;
	}

	T& pop() {
		if (curr == -1) throw out_of_range("stack is empty");

		return mem[curr--];
	}
	T& top() {
		if(curr ==-1) throw out_of_range("stack is empty");

		return mem[curr];
	}
	bool IsEmpty() {
		return curr == 0;
	}
};