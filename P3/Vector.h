#pragma once

#define BASIC_CAPACITY 8

template <typename T>
class Vector {
private:
	T* data = nullptr;
	size_t capacity = 0;
	size_t size = 0;

	void reallocate(size_t new_capacity) {
		T* temp_data = new T[new_capacity];

		// je¿eli zmniejszamy wielkosc
		if (new_capacity < size) {
			size = new_capacity;
		}

		for (int i = 0; i < size; i++) {
			temp_data[i] = data[i];
		}

		delete[] data;
		data = temp_data;
		capacity = new_capacity;
	}

	bool isInBounds(int index) const {
		if (index == 0) {
			return true;
		}
		return index > 0 && index < size;
	}

	void qsort(int l, int r) {
		if (l < r) {
			int q = partition(l, r);
			qsort(l, q);
			qsort(q + 1, r);
		}
	}

	int partition(int l, int r) {
		int pivot = data[l];
		while (true) {
			while (data[l] < pivot) {
				l = l + 1;
			}
			while (data[r] > pivot) {
				r = r - 1;
			}
			if (l < r) {
				T temp = data[l];
				data[l] = data[r];
				data[r] = temp;
				l = l + 1;
				r = r - 1;
			}
			else {
				return r;
			}
		}

	}

public:
	Vector() : size(0), capacity(BASIC_CAPACITY) {
		data = new T[capacity];
	}

	Vector(size_t size) {
		this->size = size;
		this->capacity = size;

		data = new T[size];
	}

	Vector(size_t size, T filler) : size(size), capacity(size) {
		data = new T[size];
		fill(filler);
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

	void push_back(const T& element) {
		if (size >= capacity) {
			reallocate(capacity + capacity / 2);
		}

		data[size++] = element;
	}

	//z prezentacji
	void sort() {
		qsort(0, size - 1);
	}

	void reverseSort() {
		if (!isEmpty() && size > 1) {
			sort();
			for (size_t i = 0; i < size / 2; i++) {
				T temp = data[i];
				data[i] = data[size - 1 - i];
				data[size - 1 - i] = temp;
				//std::swap(data[i], data[size - 1 - i]);
			}
		}
	}

	void pop_back() {
		if (!isEmpty()) {
			data[--size].~T();
		}
	}

	void clear() {
		for (size_t i = 0; i < size; i++) {
			data[i].~T();
		}

		size = 0;
		data = nullptr;
	}

	void fill(const T& value) {
		for (size_t i = 0; i < size; i++) {
			data[i] = value;
		}
	}

	void shrink_to_fit() {
		reallocate(size);
	}

	const T& operator[](int index) const {
		if (isInBounds(index)) {
			return data[index];
		}
		return data[0];
	}

	T& operator[](int index) {
		if (isInBounds(index)) {
			return data[index];
		}
		return data[0];
	}

	Vector<T>& operator=(const Vector<T>& other) {
		if (this == &other) {
			return *this;
		}
		delete[] data;
		size = other.size;
		capacity = other.capacity;
		data = new T[capacity];
		for (int i = 0; i < size; ++i) {
			data[i] = other.data[i];
		}
		return *this;
	}

	Vector<T>& operator=(Vector<T>&& other) noexcept {
		if (this == &other) {
			return *this;
		}
		delete[] data;

		data = other.data;
		size = other.size;
		capacity = other.capacity;

		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;

		return *this;
	}

	~Vector() {
		delete[] data;
		data = nullptr;
	}
};