#ifndef ANALYZER_H
#define ANALYZER_H

#include <set>
#include <vector>
#include <string>

class Analyzer_t{
	public:
		virtual ~Analyzer_t(){}
		Analyzer_t();
		void analyzeVect(const std::vector<std::string>& tokens, int line);
		virtual void analyzeEnd() const;
		virtual void clear();

		inline const std::set<std::string>& getTypeNames() const;
		inline const std::set<std::string>& getKeywords() const;
		inline const std::set<std::string>& getOperator() const;
		inline const std::set<std::string>& getDelimiters() const;
		inline void setTypeNames (const std::set<std::string>& types);
		inline void setKeywords (const std::set<std::string>& keys);
		inline void setOperators (const std::set<std::string>& ops);
		inline void setDelimiters (const std::set<std::string>& delims);
		
	private:
		int         c_par;
		int         c_brack;
		int         c_brace;
		int         c_if;
		int         f_typeName;
		int         c_plus;
		int         c_minus;
		int         f_main;
		std::set<std::string> m_varSet;
		std::set<std::string> m_typeNames;
		std::set<std::string> m_keywords;
		std::set<std::string> m_operators;
		std::set<std::string> m_delimiters;

		static std::string typeNames[];
		static std::string keywords[];
		static std::string operators[];
		static std::string delimiters[];
		
		Analyzer_t(const Analyzer_t& an);
		Analyzer_t& operator= (const Analyzer_t& an);
		
		bool isTypeName (const std::string& token) const;
		bool isKeyword (const std::string& token) const;
		bool isOperator (const std::string& token) const;
		bool isDelimiter (const std::string& token) const;
		virtual void checkTypeName (const std::string& token, int line);
		virtual void checkKeyword (const std::string& token, int line);
		virtual void checkOperator (const std::string& token, int line);
		virtual void checkDelimiter (const std::string& token, int line);
		virtual void checkVar(const std::string& token, int line);
	

		bool checkLegalVarName (const std::string& varName, int line) const;
		bool checkDeclared (const std::string& varName, int line);
	
		void analyzeToken (const std::string& token, int line);
		void printError(int line, std::string& message) const;
		void printEndErr(int counter, std::string brace) const;
		
		void checkAfterType (int line);
		void checkOpeningBrace (int& counter);
		void checkClosingBrace (int& counter, int line, std::string open, std::string close);
		void setPlusMinus () {c_plus = 0; c_minus = 0;}
		void checkMain(std::vector<std::string> tokens, int line);
};

inline const std::set<std::string>& Analyzer_t::getTypeNames() const { return m_typeNames;}
inline const std::set<std::string>& Analyzer_t::getKeywords() const { return m_keywords;}
inline const std::set<std::string>& Analyzer_t::getOperator() const { return m_operators;}
inline const std::set<std::string>& Analyzer_t::getDelimiters() const { return m_delimiters;}
inline void Analyzer_t::setTypeNames (const std::set<std::string>& types) { m_typeNames = types;}
inline void Analyzer_t::setKeywords (const std::set<std::string>& keys) { m_keywords = keys;}
inline void Analyzer_t::setOperators (const std::set<std::string>& ops) { m_operators = ops;}
inline void Analyzer_t::setDelimiters (const std::set<std::string>& delims) { m_delimiters = delims;}

#endif