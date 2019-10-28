#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>
	
	class Tokenizer_t{
		public:
			~Tokenizer_t(){}
			Tokenizer_t(){}
			
			inline const std::string& getDelimiters() const;
			inline void setDelimiters(const std::string delims);
			
			void tokenize(std::string& str, std::vector<std::string>& tokens);





		private:
			static std::string m_delimiters;
			
			Tokenizer_t(const Tokenizer_t&);
			Tokenizer_t& operator= (const Tokenizer_t&);	
	};

	inline const std::string& Tokenizer_t::getDelimiters() const { return m_delimiters;}
	inline void Tokenizer_t::setDelimiters(const std::string delims) { m_delimiters = delims;}
#endif