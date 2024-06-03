#pragma once
#include <iostream>

#define BASIC_CAPACITY 8

template<typename T>
class Queue
{
private:
	T* data = nullptr;
	size_t capacity = 0;
	size_t size = 0;
	int front = 0; //first element
	int rear = -1; //last element

private:

	void reallocate(size_t new_capacity) {
		T* temp_data = new T[new_capacity];

		if (new_capacity < size) {
			size = new_capacity;
		}

		for (size_t i = 0; i < size; i++) {
			temp_data[i] = data[i];
		}

		delete[] data;
		data = temp_data;
		capacity = new_capacity;
	}

public:
	Queue() : capacity(BASIC_CAPACITY), size(0) {
		data = new T[BASIC_CAPACITY];
	}
	
	Queue(size_t capacity) : capacity(capacity){
		data = new T[capacity];
	}

	void push(const T& value){
		if (size == capacity) {
			reallocate(capacity + capacity / 2);
		}
		rear = (rear + 1) % capacity;
		data[rear] = value;
		size++;
	}
	void pop() {
		if (isEmpty()) {
			throw std::runtime_error("empty queue");
		}
		//T value = data[front];
		front = (front + 1) % capacity;
		size--;
		//return value;
	}
	T getFront() const {
		if (isEmpty()) {
			throw std::runtime_error("empty queue");
		}
		return data[front];
	}
	size_t getSize() const {
		return size;
	}
	size_t getCapacity() const {
		return capacity;
	}
	bool isEmpty() const {
		return size == 0;
	}
	const T& beginning() {
		if (!isEmpty()) {
			return data[front];
		}
		throw std::runtime_error("empty queue");
	}
	const T& ending() {
		if (!isEmpty()) {
			return data[rear];
		}
		throw std::runtime_error("empty queue");
	}

	~Queue() {
		delete[] data;
		data = nullptr;
	}
};

