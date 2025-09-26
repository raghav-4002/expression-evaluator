#ifndef NODE_H_
#define NODE_H_


#include "../lexer/token.h"


/* Node types and token types will be same */
typedef Token_type Node_type;


typedef struct Tree_node
{
    Node_type type;   /* Type of node - NUMBER, "operations" */
    double    value;  /* Value of number or result of operation */

    struct Tree_node *left;  /* Left child */
    struct Tree_node *right; /* Right Child */

} Tree_node;


#endif // NODE_H_
