#include <stdlib.h>

#include "node.h"
#include "parser_helper.h"

// TODO: Handle invalid syntax and parsing errors


Tree_node *
parse_primary(Token *tokens, size_t *current)
{
    //  TODO: Add parsing for parenthesis

    Token current_token = tokens[*current];
    Token_type current_token_type = current_token.type;

    if (current_token_type == NUMBER) {
        /* Move to the next token */
        *current += 1;

        Tree_node *leaf = init_node(NULL, NUMBER, NULL);
        leaf->value = current_token.value;

        return leaf;
    }
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
