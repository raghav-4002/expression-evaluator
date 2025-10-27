#include <stdlib.h>
#include <math.h>

#include "node.h"
#include "token.h"


// TODO: Rewrite evaluator to handle unary operation

double
calculate(Tree_node *left, Tree_node *root, Tree_node *right)
{
    Node_type operation = root->type;
    double result;

    switch (operation) {
        case PLUS:
            result = left->value + right->value;
            break;

        case MINUS:
            result = left->value - right->value;
            break;

        case STAR:
            result = left->value * right->value;
            break;

        case SLASH:
            result = left->value / right->value;
            break;

        case POWER:
            result = pow(left->value, right->value);
            break;

        case UNARY_MINUS:
            result = left->value * -1;

        default:
            /* dummy case to silent compiler warning */
            break;
    }

    return result;
}


Tree_node *
evaluate_ast(Tree_node *ast_root, double *result)
{
    if (!ast_root) return NULL;
    if (ast_root->type == NUMBER) return ast_root;

    Tree_node *left = evaluate_ast(ast_root->left, result);
    Tree_node *right = evaluate_ast(ast_root->right, result);

    ast_root->value = calculate(left, ast_root, right);
    *result += ast_root->value;

    return ast_root;
}
