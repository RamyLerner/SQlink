#include "analyzer_t.h"
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <algorithm>

std::string Analyzer_t::typeNames[] = {"char", "short", "int", "long", "float", "double", "void"};
std::string Analyzer_t::keywords[] = {"if", "else", "for" , "while", "class", "private", "public", "protected", "main", "const", "virtual"};
std::string Analyzer_t::operators[] = {"++", "--", "==", "->", "=", "+", "-", "*", "&", "<<", ">>"};
std::string Analyzer_t::delimiters[] = {"(", ")", "[", "]", "{", "}", ";", "<", ">" , "=", "+", "-", "*", "&"};

Analyzer_t::Analyzer_t() : c_par(0), c_brack(0), c_brace(0), c_if(0), f_typeName(0), c_plus(0), c_minus(0), f_main(0),
    m_typeNames (typeNames, typeNames + sizeof(typeNames) / sizeof(typeNames)[0]),
    m_keywords (keywords, keywords + sizeof(keywords) / sizeof(keywords)[0]),
    m_operators (operators, operators + sizeof(operators) / sizeof(operators)[0]),
    m_delimiters (delimiters, delimiters + sizeof(delimiters) / sizeof(delimiters)[0])
    {}

void Analyzer_t::analyzeVect(const std::vector<std::string>& tokens, int line)
{
    checkMain(tokens, line);
    for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); it++)
    {   
        analyzeToken (*it,line);
    }
}

void Analyzer_t::printError(int line, std::string& message) const {
    std::cout << "Line " << line << ": Error: " << message << std::endl;
}

void Analyzer_t::analyzeToken (const std::string& token, int line){
    if (isKeyword(token))
        checkKeyword (token, line);
    else if (isTypeName(token))
        checkTypeName (token, line);
    else if (isOperator(token))
        checkOperator (token, line);
    else if (isDelimiter(token))
        checkDelimiter (token, line);  
    else
        checkVar (token, line);
}

void Analyzer_t::analyzeEnd() const{
    if (c_par > 0)
        printEndErr(c_par, "(");
    if (c_brack > 0)
        printEndErr(c_brack, "[");
    if (c_brace > 0)
        printEndErr(c_brace, "{");
}

void Analyzer_t::printEndErr(int counter, std::string brace) const{
    if (counter > 0)
        std::cout << "Error: " << counter << " \"" << brace << "\" not closed." << std::endl;
}

bool Analyzer_t::isTypeName (const std::string& token) const{
    return (std::find(m_typeNames.begin(), m_typeNames.end(), token) != m_typeNames.end());
}
		
bool Analyzer_t::isKeyword (const std::string& token) const{
    return (std::find(m_keywords.begin(), m_keywords.end(), token) != m_keywords.end());
}

bool Analyzer_t::isOperator (const std::string& token) const{
    return (std::find(m_operators.begin(), m_operators.end(), token) != m_operators.end());
}
		
bool Analyzer_t::isDelimiter (const std::string& token) const{
    return (std::find(m_delimiters.begin(), m_delimiters.end(), token) != m_delimiters.end());
}

void Analyzer_t::checkTypeName (const std::string& token, int line){
    setPlusMinus();
    if (f_typeName == 0)
        f_typeName = 1;
    else {
        std::string message = "Multiple type declarations.";
        printError(line, message);
        f_typeName = 0;
    }
}

void Analyzer_t::checkKeyword (const std::string& token, int line){
    setPlusMinus();
    checkAfterType(line);
    if (token == "if")
        c_if++;
    if (token == "else"){
        if (c_if == 0){
            std::string message = "\"else\" without \"if\"";
            printError(line, message);
        }
        else
            c_if--;
    }
}

void Analyzer_t::checkOperator (const std::string& token, int line){
    checkAfterType(line);
    if (token == "+"){
        c_minus = 0;
        if (c_plus < 2)
            c_plus++;
        else
        {
            std::string message = "Ilegal operator +++";
            printError(line, message);
            c_plus = 0;
        } 
    }
    if (token == "-"){
        c_plus = 0;
        if (c_minus < 2)
            c_minus++;
        else
        {
            std::string message = "Ilegal operator ---";
            printError(line, message);
            c_minus = 0;
        } 
    }
}

void Analyzer_t::checkDelimiter (const std::string& token, int line){
    setPlusMinus();
    checkAfterType(line);
    if (token == "(")
        checkOpeningBrace(c_par);
    else if (token == ")")
        checkClosingBrace(c_par, line, "(", ")");
    else if (token == "[")
        checkOpeningBrace(c_brack);
    else if (token == "]")
        checkClosingBrace(c_brack, line, "[", "]");
     if (token == "{")
        checkOpeningBrace(c_brace);
    else if (token == "}")
        checkClosingBrace(c_brace, line, "{", "}");

}
		
void Analyzer_t::checkVar (const std::string& token, int line){
    setPlusMinus();
    if (checkLegalVarName(token, line) ||
        checkDeclared (token, line))
    {
        if (m_varSet.insert(token).second == false){
            std::string message = "Variable " + token + " already declared.";
            printError (line, message);
        }
    }
    f_typeName = 0;
}

void Analyzer_t::checkMain(std::vector<std::string> tokens, int line){
    if (f_main == 0 && !tokens.empty()){
        if (tokens[0] != "main")
        {
            std::string message = "Illegal declaration before \"main\"";
            printError(line, message);
        }
        f_main = 1;  
    }
}

void Analyzer_t::checkAfterType(int line){
    if (f_typeName == 1){
        std::string message = "Expected variable name after type declaration.";
        printError(line, message);
        f_typeName = 0;
    }
}

void Analyzer_t::checkOpeningBrace (int& counter){
    if (counter >= 0)
        counter++;
}

void Analyzer_t::checkClosingBrace (int& counter, int line, std::string open, std::string close){
    if (counter > 0)
        counter--;
    else
    {
        std::string message = close + " without " + open; 
        printError (line, message);
    }   
}

bool Analyzer_t::checkLegalVarName (const std::string& varName, int line) const{
    char first = varName.at(0);
    if (first == '_' || isalpha(first))
        return true;
    else{
        std::string message = "Illegal variable name.";
        printError(line, message);
        return false;
    }
}

bool Analyzer_t::checkDeclared (const std::string& varName, int line){
    if (f_typeName == 1){
        f_typeName = 0;
        return true;
    }
    else{
        f_typeName = 0;
        std::string message = varName + " is not declared.";
        printError(line, message);
        return false; 
    }  
}

void Analyzer_t::clear(){
    f_typeName = 0;
    f_main = 0;
    c_par = 0;
    c_brack = 0;
    c_brace = 0;
	c_if = 0;
    c_plus = 0;
	c_minus = 0;
    m_varSet.clear();
}	