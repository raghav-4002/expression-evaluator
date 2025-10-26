#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lexer.h"
#include "input.h"


void expression(Token *tokens, size_t *current);

void
consume(size_t *current)
{
    *current += 1;
}

bool
expect(Token_type expected_type, Token *tokens, size_t *current)
{
    Token_type curr_token_type = tokens[*current].type;

    if (curr_token_type == expected_type) {
        return true;
    }

    return false;
}


void
primary(Token *tokens, size_t *current)
{
    if (expect(NUMBER, tokens, current)) {
        consume(current);
    }
    else if (expect(LEFT_PAREN, tokens, current)) {
        consume(current);
        expression(tokens, current);
        if (expect(RIGHT_PAREN, tokens, current)) {
            consume(current);
        } else {
            printf("ERROR\n");
        }
    }
    else {
        printf("ERROR\n");
    }
}


void
exponent(Token *tokens, size_t *current)
{
    primary(tokens, current);

    while (expect(POWER, tokens, current)) {
        consume(current);
        primary(tokens, current);
    }
}


void
factor(Token *tokens, size_t *current)
{
    exponent(tokens, current);

    while (expect(STAR, tokens, current) || expect(SLASH, tokens, current)) {
        consume(current);
        exponent(tokens, current);
    }
}


void
additive(Token *tokens, size_t *current)
{
    factor(tokens, current);

    while (expect(PLUS, tokens, current) || expect(MINUS, tokens, current)) {
        consume(current);
        factor(tokens, current);
    }

}

void
expression(Token *tokens, size_t *current)
{
    additive(tokens, current);
}


int
main(void)
{
    char *line = read_from_stdin();
    Token *tokens = tokenize(line);
    size_t current = 0;
    expression(tokens, &current);
}
