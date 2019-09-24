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
	inline bool operator< (const String_t& st) const;
	inline bool operator> (const String_t& st) const;
	inline bool operator<= (const String_t& st) const;
	inline bool operator>= (const String_t& st) const;
	inline bool operator== (const String_t& st) const;
	inline bool operator!= (const String_t& st) const;
	String_t& operator+= (const String_t& st);
	String_t& operator+= (const char* raw);
	char& operator[] (size_t index);
	char operator[] (size_t index) const;
	

	inline int getLength() const;
	inline const char* getString() const;
	inline static int getNumOfStrings();
	inline static int getCaseSens();
	inline static void setCaseSens(int flag);
	inline void setString(const char* s);
	
	int compareString(const String_t& st) const;
	void printString() const;
	void toLowerString();
	void toUpperString();
	String_t& prepend(const String_t& st);
	String_t& prepend(const char* raw);
	bool contains(const String_t& st) const;
	size_t firstOcc(char c) const;
	size_t lastOcc(char c) const;

private:
	char* string;
	unsigned int length;
	int capacity;

	static int numOfStrings;
	static int caseSens;
	static int defaultCapacity;

	char* createFrom(const char* s);
	char* createEmpty();
	void appendAndSet(const char *s1, const char *s2);
	static int find2power(int num);
};

inline int getLength() const{
	return length;
}
inline const char* getString() const{
	return string;
}
inline static int getNumOfStrings(){
	return numOfStrings;
}
inline static int getCaseSens(){
	return caseSens;
}
inline static void setCaseSens(int flag){
	caseSens = flag;
}


std::ostream& operator<<(std::ostream& os, const String_t& st);

#endif
