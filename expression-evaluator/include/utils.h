#ifndef UTILS_H_
#define UTILS_H_


#include <stdlib.h>
#include "token.h"
#include "node.h"


void free_tokens(Token *tokens);
void traverse_tree(Tree_node *ast_root);


#endif // UTILS_H_
