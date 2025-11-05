#pragma once

#include <iostream>

using namespace std;

template<class T>
class TQueue {
	int n;

	int s, f;//индексы первого и последнего элементов очереди

	T* mem;

public:
	TQueue(int sz = 1) {
		n = sz;
		mem = new T[n];
		s = 0; f = n - 1;
	}

	int next(int i) { return (i + 1) % n; }

	TQueue(const TQueue& q) {
		n = q.n;
		s = q.s;
		f = q.f;

		mem = new T[n];
		for (size_t i = s; i != next(f); i = next(i))
		{
			mem[i] = q.mem[i];
		}
	}

	TQueue& operator=(const TQueue& q) {
		if (this == &q) return *this;

		n = q.n;
		s = q.s; f = q.f;

		delete[] mem;
		mem = new T[n];
		for (size_t i = s; i != next(f); i = next(i))
		{
			mem[i] = q.mem[i];
		}
		return *this;
	}

	bool IsFull() { return s == next(next(f)); }//возможно что=то не так с этими двумя методами
	bool IsEmpty() { return s == next(f); }

	void push(const T& el) {
		if (IsFull()) throw out_of_range("queue is full");

		f = next(f);
		mem[f] = el;
	}

	T pop() {
		if (IsEmpty()) throw out_of_range("queue is empty");

		T res = mem[s];
		s = next(s);
		return res;

	}
	~TQueue() {
		delete[] mem;
	}

};