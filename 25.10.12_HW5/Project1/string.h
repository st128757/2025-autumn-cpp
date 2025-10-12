#ifndef STRING_SUBSTRING_H_
#define STRING_SUBSTRING_H_

#define _CRT_SECURE_NO_WARNINGS

#include <cstddef>  // For size_t
#include <cstring>  // For strlen, strcpy
#include <iostream>

struct Substring;

struct String {
public:
	String(const char* str = "");
	String(size_t n, char c);
	~String();

	String(const String& other);
	String& operator=(const String& other);

	void append(const String& other);
	Substring operator[](size_t start) const;

	char* GetStr();
	void Print() const;

private:
	size_t size;
	char* str;
};

struct Substring {
public:
	Substring(const String& string, size_t start);
	Substring(const Substring& other);
	~Substring();

	String operator[](size_t end);

private:
	size_t start;
	const String& string;
};

#endif  // STRING_SUBSTRING_H_