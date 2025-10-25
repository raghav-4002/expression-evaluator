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
    Token current_token           = tokens[*current];
    Token_type current_token_type = current_token.type;

    if (current_token_type == NUMBER) {
        /* Move to the next token */
        *current       += 1;
        Tree_node *leaf = init_node(NULL, NUMBER, NULL);

        leaf->value = current_token.value;
        return leaf;
    }

    if (current_token_type == LEFT_PAREN) {
        *current       += 1;
        Tree_node *expr = parse_expression(tokens, current);

        *current += 1;

        return expr;
    }

    return NULL;
}


static Tree_node *
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


static Tree_node *
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


/*
 * ================== WARNING =======================
 * The current parser implementation can only handle basic errors.
 
 * It can't pin-point to the exact location of the error, yet.
 
 * Also once an error is detected, the pre-mature Abstract Syntax
 * Tree is not freed, meaning memory leaks are inevitable.
 */

Tree_node *
parse_expression(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_factor(tokens, current);

    while (match_additive(tokens, current)) {
        Node_type operator = previous(tokens, *current);
        Tree_node *right   = parse_factor(tokens, current);

        expr = init_node(expr, operator, right);
    }

    return expr;
}
