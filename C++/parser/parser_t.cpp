#include "parser_t.h"
#include <fstream>

void Parser_t::parse(const string& fileName){
	ifstream inpfile(fileName);
	string str;
	int line = 1;
	m_analer.analyzeBeginning(std::string& token);
	while (!inpfile.eof()){
		getline(inpfile, str);
		m_toker.tokenize(str, m_tokenVec);
		m_analer.analyzeVect(m_tokenVec, line);
		line++;
	}
}