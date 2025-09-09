#include <stdio.h>

#include "lexer/lexer.h"
#include "io-handling/input.h"
#include "lexer/token.h"

int
main(void)
{
    char *string = read_from_stdin();

    Token *tokens = tokenize(string);

    for (size_t i = 0; tokens[i].type != NIL; i++) {
        switch (tokens[i].type) {
            case PLUS:
                printf("PLUS\n");
                break;

            case MINUS:
                printf("MINUS\n");
                break;

            case STAR:
                puts("STAR");
                break;

            case SLASH:
                puts("SLASH");
                break;

            case POWER:
                puts("POWER");
                break;

            case LEFT_PAREN:
                puts("LEFT_PAREN");
                break;

            case RIGHT_PAREN:
                puts("RIGHT_PAREN");
                break;

            case NUMBER:
                printf("%lf\n", tokens[i].number);
                break;
        }
    }
}
