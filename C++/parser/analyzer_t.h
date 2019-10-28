#ifndef ANALYZER_H
#define ANALYZER_H

#include <set>
#include <vector>
#include <string>

class Analyzer_t{
	public:
		~Analyzer_t(){}
		Analyzer_t();
		void analyzeBeginning(std::string& token);
		void analyzeVect(std::vector<std::string> tokens, int line);
		void analyzeEnd() const;
		void clear();
		
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
		void checkTypeName (const std::string& token, int line);
		void checkKeyword (const std::string& token, int line);
		void checkOperator (const std::string& token, int line);
		void checkDelimiter (const std::string& token, int line);
		void checkVar(const std::string& token, int line);
	

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

#endif