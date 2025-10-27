#include <stdlib.h>
#include <math.h>

#include "node.h"
#include "token.h"


// TODO: Rewrite evaluator to handle unary operation

double
result(double left, Node_type operation, double right)
{
    double result = 0;

    switch (operation) {
        case PLUS:
            result = left + right;
            break;
        case MINUS:
            result = left - right;
            break;

        case STAR:
            result = left * right;
            break;

        case SLASH:
            result = left / right;
            break;

        case POWER:
            result = pow(left, right);
            break;

        case UNARY_MINUS:

        default:
            break;
    }

    return result;
}


double
evaluate_ast(Tree_node *node)
{
    if (node->type == NUMBER) {
        return node->value;
    }

    double left         = evaluate_ast(node->left);
    double right        = evaluate_ast(node->right);
    Node_type operation = node->type;

    free(node->left);
    free(node->right);

    return result(left, operation, right);
}
