#ifndef PARSER_H_
#define PARSER_H_


#include <stdlib.h>

#include "node.h"

Tree_node *parse_expression(Token *tokens, size_t *current);


#endif // PARSER_H_
