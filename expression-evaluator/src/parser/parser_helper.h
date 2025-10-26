#ifndef PARSER_HELPER_H_
#define PARSER_HELPER_H_


#include <stdlib.h>
#include <stdbool.h>
#include "node.h"


typedef struct Paren_stack {
    struct Paren_stack *previous;
} Paren_stack;

Tree_node *init_node(Tree_node *expr, Node_type type, Tree_node *right);
bool expect(Token_type expected_token, Token *tokens, size_t *current);
Token_type consume(Token *tokens, size_t *current);
void push_paren(Paren_stack *paren_stack);
void pop_paren(Paren_stack *paren_stack);


#endif // PARSER_HELPER_H_
