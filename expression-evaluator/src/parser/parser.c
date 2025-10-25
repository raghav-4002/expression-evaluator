#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "node.h"
#include "parser_helper.h"

// TODO: Handle invalid syntax and parsing errors
// TODO: Add parsing support for unary operator (- and +) Tree_node *parse_expression(Token *tokens, size_t *current);


static Tree_node *
parse_primary(Token *tokens, size_t *current)
{
    Token current_token = tokens[*current];

    if (current_token.type == NUMBER) {
        /* Move to the next token */
        consume(tokens, current);
        Tree_node *leaf = init_node(NULL, NUMBER, NULL);

        leaf->value = current_token.value;
        return leaf;
    }

    if (current_token.type == LEFT_PAREN) {
        consume(tokens, current);
        Tree_node *expr = parse_expression(tokens, current);
        consume(tokens, current);

        return expr;
    }

    return NULL;
}


static Tree_node *
parse_exponent(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_primary(tokens, current);

    while (match(POWER, tokens, current)) {
        Node_type operator = consume(tokens, current);
        Tree_node *right   = parse_primary(tokens, current);

        expr = init_node(expr, operator, right);
    }

    return expr;
}


static Tree_node *
parse_factor(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_exponent(tokens, current);

    while (match(STAR, tokens, current)
        || match(SLASH, tokens, current)) {
        Node_type operator = consume(tokens, current);
        Tree_node *right   = parse_exponent(tokens, current);

        expr = init_node(expr, operator, right);
    }

    return expr;
}


Tree_node *
parse_expression(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_factor(tokens, current);

    while (match(PLUS, tokens, current)
        || match(MINUS, tokens, current)) {
        Node_type operator = consume(tokens, current);
        Tree_node *right   = parse_factor(tokens, current);

        expr = init_node(expr, operator, right);
    }

    return expr;
}
