#ifndef NODE_H_
#define NODE_H_


#include "../lexer/token.h"


/* Node types and token types will be same */
typedef Token_type Node_type;


typedef struct Tree_node
{
    Node_type type;
    double    value;
    struct Tree_node *left;
    struct Tree_node *right;

} Tree_node;


#endif // NODE_H_
