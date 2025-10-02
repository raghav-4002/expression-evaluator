#include <stdbool.h>

#include "parser_helper.h"
#include "node.h"


Tree_node *
init_node(Tree_node *expr, Node_type type, Tree_node *right)
{
    Tree_node *node = malloc(sizeof(*node));

    node->left  = expr;
    node->type  = type;
    node->right = right;

    return node;
}


bool
match_additive(Token *tokens, size_t *current)
{
    /* Move to the next token */
    *current += 1;

    size_t prev = (*current) - 1;
    Token_type prev_token_type = tokens[prev].type;

    switch (prev_token_type) {
        case PLUS: case MINUS:
            return true;

        /* false in all cases, including for last token (NIL) */
        default:
            return false;
    }
}


bool
match_factor(Token *tokens, size_t *current)
{
    /* Move to the next token */
    *current += 1;

    size_t prev = (*current) - 1;
    Token_type prev_token_type = tokens[prev].type;

    switch (prev_token_type) {
        case STAR: case SLASH:
            return true;

        default:
            return false;
    }
}


bool
match_exponent(Token *tokens, size_t *current)
{
    /* Move to the next token */
    *current += 1;

    size_t prev = (*current) - 1;
    Token_type prev_token_type = tokens[prev].type;

    switch (prev_token_type) {
        case POWER:
            return true;

        defalt:
            return false;
    }
}


Node_type
previous(Token *tokens, size_t current)
{
    return tokens[current - 1].type;
}
