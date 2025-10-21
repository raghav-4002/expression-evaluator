STD := --std=c99 --pedantic
WARNING_FLAGS := -Wall -Wextra
DEBUG_FLAG := -g
INCLUDE := -Iinclude

main:
		gcc $(WARNING_FLAGS) $(STD) $(INCLUDE) src/*.c src/lexer/*.c src/io-handling/*.c src/parser/*.c -o main

debug:
		gcc $(DEBUG_FLAG) $(WARNING_FLAGS) $(STD) $(INCLUDE) src/*.c src/lexer/*.c src/io-handling/*.c src/parser/*.c -o main
