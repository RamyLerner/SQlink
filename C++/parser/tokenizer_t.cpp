#include "tokenizer_t.h"
#include <string>
#include <vector>
#include <sstream>

Tokenizer_t::tokenize(std::string& str, std::vector<std::string>& tokens){
    size_t found;
    std::istringstream(str);
    found = str.find_first_of(m_delimiters);
    while(str.getline(check1, intermediate, ' ')
}