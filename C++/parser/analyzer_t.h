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
		void analyzeVect(vector<std::string> tokens, int line);
		void analyzeEnd() const;
		void clear();
		
	private:
		int         c_par;
		int         c_brack;
		int         c_brace;
		int         c_if;
		int         f_typeNmae;
		int         f_plus;
		int         f_minus;
		set<string> varSet;
		
		Analyzer_t(const Analyzer_t& an);
		Analyzer_t& operator= (const Analyzer_t& an);
		
		static bool isLegalVarName (const std::string& varName);
		void analyzeToken (const std::string& token);
		void analyzeVect (const vector<std::string>& tokens);
		
		void checkTypeName (const std::string& token);
		void checkAfterType (const std::string& token);
		void checkBraces (const std::stinrg& token);
		void checkElse (const std::string& token);
		void checkPlusMinus (const std::string& token);
		void checkDupVarDeclaration (const std::string& token);
};

#endif