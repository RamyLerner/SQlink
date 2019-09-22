#include <string.h>
#include "string_t.h"
#include <cstdio>

String_t ::String_t()
{
	string = "";
	length = 0;
}

String_t ::String_t(const char *s)
{
	if (!s)
	{
		string = "";
		length = 0;
	}
	else
	{
		string = createFrom(s);
		length = strlen(s);
	}
}

String_t ::String_t(const String_t &st)
{
	string = createFrom(st.string);
	length = st.length;
}

String_t ::~String_t()
{
	delete[] string;
}

String_t &String_t ::operator=(const String_t &st)
{
	if (this != &st)
	{
		length = st.length;
		delete[] string;
		string = createFrom(st.string);
	}
	return *this;
}

int String_t ::getLength() const
{
	return length;
}

void String_t ::setString(const char *s)
{
	delete[] string;
	if (!s){
		string = "";
		length = 0;
	}
	else{
		string = createFrom(s);
		length = strlen(s);
	}
}

const char *String_t ::getString() const
{
	return string;
}

int String_t ::compareString(const String_t &st) const
{
	int res = strcmp(string, st.string);
	if (!res)
		return 0;
	return res < 0 ? 1 : 2;
}

void String_t ::printString() const
{
		printf("length: %d. string: %s\n", length, string);
}