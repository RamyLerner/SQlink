#include "parser_t.h"
#include "tokenizer_t.h"
#include "analyzer_t.h"
#include <fstream>

Parser_t::~Parser_t(){
	delete m_analer;
	delete m_toker;
}

Parser_t::Parser_t(){
	m_analer = new Analyzer_t();
	m_toker = new Tokenizer_t();
}

void Parser_t::parse(const char* fileName){
	std::ifstream inpfile(fileName);
	std::string str;
	int line = 1;
	while (!inpfile.eof()){
		getline(inpfile, str);
		m_toker->tokenize(str, m_tokenVec);
		m_analer->analyzeVect(m_tokenVec, line);
		line++;
		m_tokenVec.clear();
	}
	m_analer->analyzeEnd();
	m_analer->clear();
}
