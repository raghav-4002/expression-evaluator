CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -pedantic
IFLAGS := -Iinclude
DEBUG := -g

all:
		$(CC) $(CFLAGS) $(IFLAGS) src/io-handling/*.c src/lexer/*.c src/parser/*.c src/evaluator/*.c src/*.c -lm -o main

debug:
		$(CC) $(CFLAGS) $(IFLAGS) $(DEBUG) src/io-handling/*.c src/lexer/*.c src/parser/*.c src/evaluator/*.c src/*.c -lm -o main
