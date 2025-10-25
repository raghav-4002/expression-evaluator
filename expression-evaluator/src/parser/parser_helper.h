#ifndef PARSER_HELPER_H_
#define PARSER_HELPER_H_


#include <stdlib.h>
#include <stdbool.h>
#include "node.h"

Tree_node *init_node(Tree_node *expr, Node_type type, Tree_node *right);
bool match(Token_type expected_token, Token *tokens, size_t *current);
Node_type previous(Token *tokens, size_t current);


#endif // PARSER_HELPER_H_
