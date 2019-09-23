#ifndef STRING_H
#define STRING_H

#define STR_MAX_SIZE 256
#include <iostream>

class String_t{
public:
	~String_t();
	String_t();
	String_t(const char* s);
	String_t(const String_t& st);
	
	String_t& operator= (const String_t& st);
	bool operator< (const String_t& st);
	bool operator> (const String_t& st);
	bool operator<= (const String_t& st);
	bool operator>= (const String_t& st);
	bool operator== (const String_t& st);
	bool operator!= (const String_t& st);
	String_t& operator+= (const String_t& st);
	String_t& operator+= (const char* raw);
	char& operator[] (size_t index);
	const char operator[] (size_t index) const;
	
	int getLength() const;
	void setString(const char* s);
	const char* getString() const;
	int compareString(const String_t& st) const;
	void printString() const;
	void toLowerString();
	void toUpperString();
	void prepend(const String_t& st);
	void prepend(const char* raw);
	bool contains(const String_t& st) const;

private:
	char* string;
	unsigned int length;

	char* createFrom(const char* s);

	char* createEmpty();

};

std::ostream& operator<<(std::ostream& os, const String_t& st);

#endif