#pragma once
#include <iostream>

template <typename T>
struct Box {
	T data;
	Box* next; //wskaŸnik na nastêpny element
};


template <typename T>
class LinkedList
{
private:
	Box<T>* head;
public:
	LinkedList() : head(nullptr) {};

	void push(T data) {
		Box<T>* newPrep = new Box<T>{ data, nullptr };

		if (head == nullptr) {
			head = newPrep;
		}
		else {
			Box<T>* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = newPrep;
		}
	}

	T pop() {
		if (isEmpty()) {
			std::cout << "PUSTY" << std::endl;
			throw std::out_of_range("");
		}
		else {
			Box<T>* temp = head;
			head = head->next;
			T value = temp->data;
			delete temp;
			return value;
		}
	}

	T popLast() {
		if (isEmpty()) {
			std::cout << "PUSTY" << std::endl;
			throw std::out_of_range(""); 
		}
		else {
			if (head->next == nullptr) {
				T value = head->data;
				delete head;
				head = nullptr;
				return value;
			}

			Box<T>* temp = head;
			bool done = false;

			//temp na przedostatni element
			while (!done) {
				if (temp->next->next == nullptr) {
					done = true;
				}
				else {
					temp = temp->next;
				}
			}
			T value = temp->next->data;
			delete temp->next;
			temp->next = nullptr;
			return value;
		}
	}

	void print() const {
		Box<T>* current = head;
		
		while (current != nullptr) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}

	int size() const {
		Box<T>* current = head;
		int size = 0;
		if (current == nullptr) {
			return size;
		}
		
		while (current != nullptr) {
			size++;
			current = current->next;
		}
		return size;
	}

	bool isEmpty() const {
		return head == nullptr;
	}

	T& getTopData() const {
		if (isEmpty()) {
			std::cout << "PUSTY" << std::endl;
			throw std::out_of_range("");
		}
		else {
			Box<T>* temp = head;

			while (temp->next != nullptr) {
				temp = temp->next;
			}

			return temp->data;
		}
	}

	void show() const {
		Box<T>* current = head;
		while (current != nullptr) {
			std::cout << current->data << " ";
			current = current->next;
		}
	}

	void showReverse(Box<T>* current) const {
		if (current == nullptr) {
			return;
		}
		showReverse(current->next);
		std::cout << current->data << " ";
	}

	void showReverse() const {
		showReverse(head);
	}

	~LinkedList() {
		Box<T>* current = head;
		while (current != nullptr) {
			Box<T>* next = current->next;
			delete current;
			current = next;
		}
	}

};

