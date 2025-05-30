CC = gcc
CFLAGS = -Wall -Wno-unused-function -g

# Default target
all: compiler

# Generate the parser
parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

# Generate the lexer
lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

# Compile the compiler
compiler: lex.yy.c parser.tab.c
	$(CC) $(CFLAGS) -o compiler lex.yy.c parser.tab.c -lfl

# Clean generated files
clean:
	rm -f lex.yy.c parser.tab.c parser.tab.h compiler output.ac3

# Test with the example input
test: compiler
	./compiler < test_input.txt

.PHONY: all clean test 