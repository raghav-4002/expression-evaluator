STD := --std=c99 --pedantic
WARNING_FLAGS := -Wall -Wextra
DEOPTIMIZATION_FLAGS := -g

main:
		gcc $(WARNING_FLAGS) $(STD) src/*.c src/lexer/*.c src/io-handling/*.c src/parser/*.c

debug:
		gcc $(DEOPTIMIZATION_FLAGS) g $(WARNING_FLAGS) $(STD) src/*.c src/lexer/*.c src/io-handling/*.c src/parser/*.c
