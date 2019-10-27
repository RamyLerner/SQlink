#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>
	
	class Tokenizer_t(){
		public:
			~Tokenizer_t();
			Tokenizer_t();
			
			const std::string& getDelimiters() const;
			
			void tokenize(std::string& str, std::vector<std::string>& tokens);
			
			
			
		
		private:
			std::string delimiters;
			
			Tokenizer_t(const Tokenizer_t&);
			Tokenizer_t& operator= (const Tokenizer_t&);	
	};
#endif