#ifndef PARSER_HELPER_H_
#define PARSER_HELPER_H_


#include <stdlib.h>
#include <stdbool.h>
#include "parser/node.h"

Tree_node *init_node(Tree_node *expr, Node_type type, Tree_node *right);
bool match_additive(Token *tokens, size_t *current);
bool match_factor(Token *tokens, size_t *current);
bool match_exponent(Token *tokens, size_t *current);
Node_type previous(Token *tokens, size_t current);


#endif // PARSER_HELPER_H_
