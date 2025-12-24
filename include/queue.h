#pragma once

#include <iostream>

using namespace std;

template<class T>
class TQueue {
	int n;

	int s, f;//индексы первого и последнего элементов очереди
	int count;

	T* mem;

public:
	TQueue(int sz = 200) {
		n = sz;
		mem = new T[n];
		s = 0; /*f = n - 1;*/
		f = -1;
		count = 0;
	}

	int next(int i) { return (i + 1) % n; }

	TQueue(const TQueue& q) {
		n = q.n;
		s = q.s;
		f = q.f;
		count = q.count;

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
		count = q.count;

		delete[] mem;
		mem = new T[n];
		for (size_t i = s; i != next(f); i = next(i))
		{
			mem[i] = q.mem[i];
		}
		return *this;
	}

	bool IsFull() { /*return next(next(f)) == s;*/
		return count == n;
	}//возможно что=то не так с этими двумя методами
	bool IsEmpty() { /*return s == next(f);*/
		return count == 0;
	}

	void push(const T& el) {
		if (IsFull()) throw out_of_range("queue is full");

		f = next(f);
		if (f == -1) f = 0;
		mem[f] = el;
		count++;
	}

	T pop() {
		if (IsEmpty()) throw out_of_range("queue is empty");

		T res = mem[s];
		s = next(s);
		count--;
		if (IsEmpty()) {
			s = 0;
			f = -1;
		}
		return res;

	}
	~TQueue() {
		delete[] mem;
	}

};