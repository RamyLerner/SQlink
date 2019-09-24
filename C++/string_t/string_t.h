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
	bool operator< (const String_t& st) const;
	bool operator> (const String_t& st) const;
	bool operator<= (const String_t& st) const;
	bool operator>= (const String_t& st) const;
	bool operator== (const String_t& st) const;
	bool operator!= (const String_t& st) const;
	String_t& operator+= (const String_t& st);
	String_t& operator+= (const char* raw);
	char& operator[] (size_t index);
	char operator[] (size_t index) const;
	

	inline size_t          getLength() const;
	inline const char*     getString() const;
	inline static int      getNumOfStrings();
	inline static int      getCaseSens();
	inline static size_t   getDefaultCapacity();
	inline static void     setCaseSens(int flag);
	inline static void     setDefaultCapacity(size_t capacity);
	void                   setString(const char* s);
	
	int compareString(const String_t& st) const;
	void printString() const;
	void toLowerString();
	void toUpperString();
	String_t& prepend(const String_t& st);
	String_t& prepend(const char* raw);
	bool contains(const String_t& st) const;
	int firstOcc(char c) const;
	int lastOcc(char c) const;

private:
	char* string;
	size_t length;
	size_t capacity;

	static int numOfStrings;
	static int caseSens;
	static size_t defaultCapacity;

	static char* createFrom(const char* s);
	static char* createEmpty();
	void appendAndSet(const char *s1, const char *s2);
	static unsigned int find2power(unsigned int num);
};

inline size_t String_t::getLength() const{ return length;}
inline const char* String_t::getString() const{ return string;}
inline  int String_t::getNumOfStrings(){ return numOfStrings;}
inline  int String_t::getCaseSens(){ return caseSens;}
inline  void String_t::setCaseSens(int flag){ caseSens = flag;}
inline  size_t  String_t::getDefaultCapacity(){ return defaultCapacity;}
inline  void String_t::setDefaultCapacity(size_t cap){ defaultCapacity = cap;}

std::ostream& operator<<(std::ostream& os, const String_t& st);

#endif
