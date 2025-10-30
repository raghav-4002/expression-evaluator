#ifndef PARSER_H_
#define PARSER_H_


#include <stdlib.h>

#include "node.h"

Tree_node *parse_expression(Token *tokens, size_t *current);
Tree_node *parse_tokens(Token *tokens);


#endif // PARSER_H_
