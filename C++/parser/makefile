CFLAGS  = -ansi -pedantic -g -Wall

go : testParser.o analyzer_t.o tokenizer_t.o parser_t.o
	g++ -o go testParser.o analyzer_t.o tokenizer_t.o parser_t.o

testParser.o : testParser.cpp parser_t.h
	g++ -c $(CFLAGS) testParser.cpp

analyzer_t.o : analyzer_t.cpp analyzer_t.h
	g++ -c $(CFLAGS) analyzer_t.cpp

tokenizer_t.o : tokenizer_t.cpp tokenizer_t.h
	g++ -c $(CFLAGS) tokenizer_t.cpp

parser_t.o : parser_t.cpp parser_t.h tokenizer_t.h analyzer_t.h
	g++ -c $(CFLAGS) parser_t.cpp

