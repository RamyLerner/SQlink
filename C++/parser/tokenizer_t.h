#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>
	
	class Tokenizer_t(){
		public:
			~Tokenizer_t();
			Tokenizer_t();
			
			const vector<char>& getDelimiters() const;
			const vector<char>& getWhitespaves() const;
			
			void tokenize(std::string& str, vector<std::string>& tokens);
			
			
			
		
		private:
			vector<char> delimiters;
			vector<char> whiteSpaces;
			
			Tokenizer_t(const Tokenizer_t&);
			Tokenizer_t& operator= (const Tokenizer_t&);	
	};
#endif