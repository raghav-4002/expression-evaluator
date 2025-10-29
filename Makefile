CC := gcc
CFLAGS := -Wall -Wextra 
IFLAGS := -Iinclude -Ilibs
DEBUG := -g

all:
		$(CC) $(CFLAGS) $(IFLAGS) src/io-handling/*.c src/lexer/*.c src/parser/*.c src/evaluator/*.c src/*.c libs/linenoise/linenoise.c -lm -o eval

debug:
		$(CC) $(CFLAGS) $(IFLAGS) $(DEBUG) src/io-handling/*.c src/lexer/*.c src/parser/*.c src/evaluator/*.c src/*.c libs/linenoise/linenoise.c -lm -o eval
