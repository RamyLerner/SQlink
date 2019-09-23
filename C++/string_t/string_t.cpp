#include <string.h>
#include "string_t.h"
#include <iostream>
#include <ctype.h>


String_t::String_t()
{
	string = createEmpty();
	length = 0;
}

String_t::String_t(const char *s)
{
	if (!s)
	{
		string = createEmpty();
		length = 0;
	}
	else
	{
		string = createFrom(s);
		length = strlen(s);
	}
}

String_t::String_t(const String_t &st)
{
	string = createFrom(st.string);
	length = st.length;
}

String_t::~String_t()
{
	delete[] string;
}

String_t &String_t::operator=(const String_t &st)
{
	if (this != &st)
	{
		length = st.length;
		delete[] string;
		string = createFrom(st.string);
	}
	return *this;
}

int String_t::getLength() const
{
	return length;
}

void String_t::setString(const char *s)
{
	delete[] string;
	if (!s)
	{
		string = createEmpty();
		length = 0;
	}
	else
	{
		string = createFrom(s);
		length = strlen(s);
	}
}

const char *String_t::getString() const
{
	return string;
}

int String_t::compareString(const String_t& st) const
{
	int res = strcmp(string, st.string);
	if (!res)
		return 0;
	return res < 0 ? 1 : 2;
}


void String_t::toLowerString()
{
	int i = 0;
	while (string[i])
	{
		string[i] = tolower(string[i]);
		i++;
	}
}

void String_t::toUpperString()
{
	int i = 0;
	while (string[i])
	{
		string[i] = toupper(string[i]);
		i++;
	}
}

void append() {}

void String_t::prepend(const char *raw)
{
	char temp[STR_MAX_SIZE];
	int rawSize = strlen(raw);
	strcpy(temp, string);
	delete[] string;
	string = new char[length + rawSize];
	strcpy(string, raw);
	strcat(string, temp);
	length += rawSize;
}

void String_t::prepend(const String_t& st)
{
	prepend(st.string);
}

String_t& String_t::operator+=(const char *raw)
{
	char temp[STR_MAX_SIZE];
	int rawSize = strlen(raw);
	strcpy(temp, string);
	delete[] string;
	string = new char[length + rawSize];
	strcpy(string, temp);
	strcat(string, raw);
	length += rawSize;
	return *this;
}

String_t& String_t::operator+=(const String_t& st)
{
	return *this += st.string;
}

bool String_t::operator<(const String_t& st){
	return compareString(st) == 1 ? true : false;
}

bool String_t::operator>(const String_t& st){
	return compareString(st) == 2 ? true : false;
}

bool String_t::operator<=(const String_t& st){
	return compareString(st) != 2 ? true : false;
}

bool String_t::operator>=(const String_t& st){
	return compareString(st) != 1 ? true : false;
}

bool String_t::operator==(const String_t& st){
	return compareString(st) == 0 ? true : false;
}

bool String_t::operator!=(const String_t& st){
	return compareString(st) != 0 ? true : false;
}

char& String_t::operator[] (size_t index){
	if (index >= length){
		return string[length];
	}
	else return string[index];
}

const char String_t::operator[] (size_t index) const{
	if (index >= length)
		return 0;
	else return string[index];
}

bool String_t::contains(const String_t& st) const{
	return strstr(string, st.string) ? true : false;
}

std::ostream& operator<<(std::ostream& os, const String_t& st){
	os << st.getString();
	return os;
}

void String_t::printString() const
{
	std::cout << *this;
}

char* String_t::createFrom(const char *s)
{
	char *temp = new char[strlen(s) + 1];
	strcpy(temp, s);
	return temp;
}

char* String_t::createEmpty()
{
	char *s = new char[4];
	s[0] = '\0';
	return s;
}