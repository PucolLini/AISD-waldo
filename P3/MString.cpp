#include "MString.h"

int MString::getSize() const {
	return size;
}

bool MString::isEmpty() const {
	return size == 0;
}

int MString::toNumber() const {
	int number = 0;

	for (int i = 0; i < size; i++) {
		if (data[i] < '0' || data[i]>'9') {
			return -1;
		}
		number = number * 10 + (data[i] - '0');
	}

	return number;
}

MString MString::toString(int number)
{
	if (number == 0)
	{
		return MString("0");
	}

	int temp = number;
	int size = 0;
	while (temp != 0)
	{
		temp /= 10;
		size++;
	}

	MString result;
	for (int i = 0; i < size; i++)
	{
		result += 'x';
	}
	for (int i = size - 1; i >= 0; i--)
	{
		result.data[i] = number % 10 + '0';
		number /= 10;
	}

	return result;
}

MString MString::substr(int start, int count) const
{
	if (start < 0 || count < 0 || start > size || count + start > size)
	{
		throw "Out of bounds!";
	}

	MString result;
	for (int i = start; i < count + start; i++)
	{
		result += data[i];
	}
	return result;
}

MString::MString() : size(0), data(new char[1]) {
	data[0] = '\0';
}

MString::MString(const char* str) {
	this->size = strlen(str);
	this->data = new char[size + 1];
	strcpy_s(data, size + 1, str);
}

MString::MString(const MString& str) {
	size = str.size;
	data = new char[size + 1];
	strcpy_s(data, size + 1, str.data);
}

void MString::operator+=(char c) {
	char* result = new char[size + 2];
	strcpy_s(result, size + 1, data);
	result[size] = c;
	result[size + 1] = '\0';

	if (data != nullptr)
	{
		delete[] data;
		//size = 0;
	}
	data = result;
	size++;
}

void MString::operator+=(MString str) {
	int opSize = str.getSize();
	char* result = new char[size + 1 + opSize];
	strcpy_s(result, size + opSize, data);

	for (int i = size; i < size + opSize; i++) {
		result[i] = str[i - size];
	}
	result[size+opSize] = '\0';

	if (data != nullptr)
	{
		delete[] data;
	}
	data = result;
	size = size + opSize;
}

void MString::operator=(const MString& str) {
	if (this != &str) {
		if (data != nullptr)
		{
			delete[] data;
		}
		size = str.size;
		data = new char[size + 1];
		strcpy_s(data, size + 1, str.data);
	}
}

void MString::operator=(const char* str) {
	if (data != nullptr)
	{
		delete[] data;
	}
	if (strcmp(str, "")) {
		size = 0;
	}
	else {
		size = strlen(str) + 1;
	}
	data = new char[size + 1];
	strcpy_s(data, size + 1, str);
}

void MString::operator=(const char c) {
	if (data != nullptr)
	{
		delete[] data;
	}
	size = 2;
	data = new char[2];
	data[0] = c;
	data[1] = '\0';
}

bool MString::operator==(const MString str) const {
	int counter = 0;
	if (size == str.size) {
		for (int i = 0; i < str.size; i++) {
			if (data[i] == str.data[i])
				counter++;
		}
	}
	if (counter != size)
		return false;
	else return true;
}

bool MString::operator==(const char c) const {
	return (size == 2 && data[0] == c);
}

bool MString::operator==(const char* str) const {
	int counter = 0;
	int str_size = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		str_size++;
		if (data[i] == str[i]) {
			counter++;
		}
	}
	if (size == str_size) {
		if (counter == size) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool MString::operator!=(const char* str) const {
	return !(*this == str);
}

bool MString::operator!=(const MString str) const {
	return !(*this == str);
}

char& MString::operator[](const int& index) {
	if (index >= 0 && index < size) {
		return data[index];
	}
	throw std::out_of_range("");
}

MString::~MString() {
	if (size != 0 && data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}