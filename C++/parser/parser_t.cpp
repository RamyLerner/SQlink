#include "parser_t.h"
#include "tokenizer_t.h"
#include "analyzer_t.h"
#include <fstream>

void Parser_t::parse(const std::string& fileName){
	std::ifstream inpfile(fileName);
	std::string str;
	int line = 1;
	//m_analer->analyzeBeginning(std::string& token);
	while (!inpfile.eof()){
		getline(inpfile, str);
		m_toker->tokenize(str, m_tokenVec);
		m_analer->analyzeVect(m_tokenVec, line);
		line++;
	}
	m_analer->anlayzeEnd();
}
