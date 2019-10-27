#ifndef ANALYZER_H
#define ANALYZER_H

#include <set>
#include <vector>
#include <string>

class Analyzer_t{
	public:
		~Analyzer_t();
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
		int         f_plus;
		int         f_minus;
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
		
		static bool isLegalVarName (const std::string& varName);
		void analyzeToken (const std::string& token, int line);
		
		void checkTypeName (const std::string& token, int line);
		void checkAfterType (const std::string& token, int line);
		void checkBraces (const std::string& token, int line);
		void checkElse (const std::string& token, int line);
		void checkPlusMinus (const std::string& token, int line);
		void checkDupVar (const std::string& token, int line);
		void checkAfterPM (const std::string& token, int linest)
};

#endif