#include "parser_t.h"

int main(int argc, char** argv){
    int i = 0;
    Parser_t parser;
    for (i=1; i<argc; i++)
        parser.parse(argv[i]);
}