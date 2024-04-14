#pragma once
#include <iostream>
#include <string.h>

inline void strcopy(char* dst, const char* src) {
	int i = 0;
	for (i; src[i] != '\0'; i++) {
		dst[i] = src[i];
	}
	dst[i] = '\0';
}

class MString
{
private:
	size_t size;
	char* data;

public:
	friend std::ostream& operator<<(std::ostream& os, MString str) {
		return os << str.data;
	}
	char* getData() const;
	int getSize() const;
	int toNumber() const;
	static MString toString(int number);
	MString substr(int start, int end) const;
	void clear();
	MString();
	MString(const char* str);
	MString(const MString& str);
	void operator+=(char c);//str
	void operator+=(MString str);//str
	void operator=(const MString& str); //str
	void operator=(const char* str);//str
	void operator=(const char c); //str
	bool operator==(const MString str) const; //&
	bool operator==(const char c) const;
	bool operator==(const char* str) const;
	bool operator!=(const char* str) const;
	bool operator!=(const MString str) const;
	char& operator[](const int& index);

	~MString();
};