#include "tokenizer_t.h"
#include <cctype>
#include <string>
#include <vector>
#include <sstream>

std::string Tokenizer_t::m_delimiters = "()[]{}<>;=+-*& \n\t\v\f\r";

Tokenizer_t::tokenize(std::string &str, std::vector<std::string> &tokens)
{
    size_t found,start = 0;
    std::string token;

    found = str.find_first_of(m_delimiters);
    while (found != std::string::npos)
    {
        token = substr (start, found - start);
        tokens.push_back(token);
        if (!isspace(str[found]))
        {
            tokens.push_back(str[found]);
        }
        start = found+1;
        found = str.fine_first_of(m_delimiters, found+1);
    }
}