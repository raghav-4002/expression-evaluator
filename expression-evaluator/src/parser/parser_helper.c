#include <stdio.h>
#include <stdbool.h>

#include "parser_helper.h"
#include "node.h"
#include "token.h"


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


Token_type
consume(Token *tokens, size_t *current)
{
    *current += 1;
    return tokens[*current - 1].type;
}


bool
match(Token_type expected_token_type, Token *tokens, size_t *current)
{
    Token_type current_token_type = tokens[*current].type;

    if (current_token_type == expected_token_type) return true;

    return false;
}
