#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

class Parser_t{
	public:
		~Parser_t();
		Parser_t();
		
		inline const  vector<string>& getTokenVec() const;
		void parse (const string& fileName);
		
	private:
		vector<string> m_tokenVec;
		tokenizer_t m_toker;
		analyzer_t m_analer;
		
		Parser_t(const Parser_t& p);
		Parser_t& operator= (const Parser_t& p);
		
		
		
};

inline const vector<string>& getTokenVec() const { return tokenVec;}

#endif