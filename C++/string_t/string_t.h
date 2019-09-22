#ifndef STRING_H
#define STRING_H

#include <string.h>

class String_t{
public:
	String_t();
	String_t(const char* s);
	String_t(const String_t& st);
	~String_t();
	
	String_t& operator= (const String_t& st);
	
	int getLength() const;
	void setString(const char* s);
	const char* getString() const;
	int compareString(const String_t& st) const;
	void printString() const;

private:
	char* string;
	int length;
	char* createFrom(const char* s){
		char* temp = new char[strlen(s) + 1];
		strcpy(temp, s);
		return temp;
	}

};

#endif