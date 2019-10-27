#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

class Parser_t{
	public:
		~Parser_t();
		Parser_t();
		
		inline const std::vector<std::string>& getTokenVec() const;
		void parse (const std::string& fileName);
		
	private:
		std::vector<std::string> m_tokenVec;
		tokenizer_t*   m_toker;
		analyzer_t*    m_analer;
		
		Parser_t(const Parser_t& p);
		Parser_t& operator= (const Parser_t& p);
		
		
		
};

inline const std::vector<std::string>& getTokenVec() const { return m_tokenVec;}

#endif