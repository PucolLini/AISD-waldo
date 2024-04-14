#pragma once
#include "LinkedList.h"
// LIFO stack

template <typename T> 
class Stack {
private:
	LinkedList<T> list;

public:
	Stack() {};

	void push(T element) {
		list.push(element);
	};

	T pop() {
		return list.popLast();
	}; 

	bool isEmpty() const {
		return list.isEmpty();
	};
	int size() const {
		return list.size();
	};
	T& top() {
		return list.getTopData();
	};
	T& getElement(int index) {
		index++;
		T* tmpArr = new T[index];
		for (int i = 0; i < index - 1; i++) {
			tmpArr[i] = list.popLast();
		}
		T& result = list.getTopData();
		for (int i = index - 2; i >= 0; i--) {
			list.push(tmpArr[i]);
		}
		delete[] tmpArr;
		return result;
	}

	void show() const {
		list.show();
	}

	void showReverse() const {
		list.showReverse();
	}

	~Stack() {};
};

