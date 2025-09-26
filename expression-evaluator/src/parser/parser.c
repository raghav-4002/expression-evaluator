#include <stdlib.h>

#include "parser.h"


Tree_node *
parse_factor(Token *tokens, size_t start, size_t end)
{
    size_t i = start;

    while (tokens[i].type != STAR && tokens[i].type != SLASH
        && tokens[i].type != NIL) {

        i++;
    }

    if (tokens[i].type == NIL) {
        return parse_exponent(tokens);
    }
}


Tree_node *
parse_expression(Token *tokens)
{
    size_t i = 0;

    while (tokens[i].type != PLUS && tokens[i].type != MINUS
        && tokens[i].type != NIL) {

        i++;
    }

    /* If end of tokens is reached, simply
     * return the tree of factor */
    if (tokens[i].type == NIL) {
        return parse_factor(tokens);
    }
}


Tree_node *
parse(Token *tokens)
{
    return parse_expression(tokens);
}
