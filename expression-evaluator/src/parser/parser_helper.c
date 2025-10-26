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
expect(Token_type expected_token_type, Token *tokens, size_t *current)
{
    Token_type current_token_type = tokens[*current].type;

    if (current_token_type == expected_token_type) return true;

    return false;
}


void
push_paren(Paren_stack **paren_stack)
{
    Paren_stack *new = malloc(sizeof(*paren_stack));
    new->previous = *paren_stack;
    *paren_stack = new;
}


void
pop_paren(Paren_stack **paren_stack)
{
    if (*paren_stack) {
        Paren_stack *prev = (*paren_stack)->previous;
        free(*paren_stack);
        *paren_stack = prev;
    }
}


static void
empty_stack(Paren_stack **paren_stack)
{
    while (*paren_stack) {
        pop_paren(paren_stack);
    }
}


static void
destroy_tree(Tree_node *root)
{
    if (!root) return;

    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}


void
wrap_up_parser(Tree_node *root, Paren_stack **paren_stack)
{
    empty_stack(paren_stack);
    destroy_tree(root);
}
