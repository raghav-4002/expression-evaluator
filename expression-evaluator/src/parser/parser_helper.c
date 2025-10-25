#include <stdio.h>
#include <stdbool.h>

#include "parser_helper.h"
#include "node.h"


Tree_node *
init_node(Tree_node *expr, Node_type type, Tree_node *right)
{
    Tree_node *node = malloc(sizeof(*node));

    if (!node) {
        perror(NULL);
        return NULL;
    }

    node->left  = expr;
    node->type  = type;
    node->right = right;

    return node;
}


bool
match_additive(Token *tokens, size_t *current)
{
    Token_type current_token_type = tokens[*current].type;

    switch (current_token_type) {
        case PLUS: case MINUS:
            *current += 1;
            return true;

        default:
            return false;
    }
}


bool
match_factor(Token *tokens, size_t *current)
{
    Token_type current_token_type = tokens[*current].type;

    switch (current_token_type) {
        case STAR: case SLASH:
            *current += 1;
            return true;

        default:
            return false;
    }
}


bool
match_exponent(Token *tokens, size_t *current)
{
    Token_type current_token_type = tokens[*current].type;

    switch (current_token_type) {
        case POWER:
            *current += 1;
            return true;

        default:
            return false;
    }
}


Node_type
previous(Token *tokens, size_t current)
{
    return tokens[current - 1].type;
}
