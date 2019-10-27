#include "analyzer_t.h"
#include <string>
#include <vector>

std::string Analyzer_t::typeNames[] = {"char", "short", "int", "long", "float", "double", "void"};
std::string Analyzer_t::keywords[] = {"if", "else", "for" , "while", "class", "private", "public", "protected", "main", "const", "virtual"};
std::string Analyzer_t::operators[] = {"++", "--", "==", "->", "=", "+", "-", "*", "&", "<<", ">>"};
std::string Analyzer_t::delimiters[] = {"(", ")", "[", "]" , "{" , "}" ";" "<", ">" , "=", "+", "-", "*", "&"};

Analyzer_t::Analyzer_t() : c_par(0), c_brack(0), c_brack(0), c_if(0), f_typeName(0), f_plus(0), f_minus(0),
    m_typeNames (std::begin(typeNames), std::end(typeNames)),
    m_keywords (std::begin(keywords), std::end(keywords)),
    m_operators (std::begin(operators), std::end(operators)),
    m_delimiters (std::begin(delimiters), std::end(delimiters))
    {}

void Analyzer_t::analyzeVect(std::vector<std::string> tokens, int line)
{
    for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++)
    {   
        analyzeToken (*it,line);
    }
}

void Analyzer_t::analyzeToken (const std::string& token, int line){
    
    checkTypeName(token, line);
    checkAfterType(token, line);

    checkBraces(token, line);
    
    checkElse(token, line);
    checkPlusMinus(token, line);
    checkDupVar(token, line);
    checkAfterPM(token, line);
}



