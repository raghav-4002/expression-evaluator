#include <stdlib.h>

#include "node.h"
#include "parser_helper.h"


Tree_node *
parse_primary(Token *tokens, size_t *current)
{
    //TODO: Complete primary expression parsing
}


Tree_node *
parse_exponent(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_primary(tokens, current);

    while (match_exponent(tokens, current)) {
        Node_type operator = previous(tokens, *current);
        Tree_node *right   = parse_primary(tokens, current);

        expr = init_node(expr, operator, right);
    }

    return expr;
}


Tree_node *
parse_factor(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_exponent(tokens, current);

    while (match_factor(tokens, current)) {
        Node_type operator = previous(tokens, *current);
        Tree_node *right   = parse_exponent(tokens, current);

        expr = init_node(expr, operator, right);
    }

    return expr;
}


Tree_node *
parse_expression(Token *tokens)
{
    size_t current  = 0;
    Tree_node *expr = parse_factor(tokens, &current);

    while (match_additive(tokens, &current)) {
        Node_type operator = previous(tokens, current);
        Tree_node *right   = parse_factor(tokens, &current);

        expr = init_node(expr, operator, right);
    }

    return expr;
}
