#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "token.h"
#include "evaluator.h"


// TODO: Rewrite evaluator to handle unary operation


void
free_children_nodes(Tree_node *left, Tree_node *right)
{
    free(left);
    free(right);
}


int
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
            if (!right->value) {
                fprintf(stderr, "Dividing %lf with zero is invalid\n", left->value);
                return -1;
            }

            result = left->value / right->value;
            break;

        case POWER:
            if (!left->value && !right->value) {
                fprintf(stderr, "0 raised to the power 0 is invalid\n");
                return -1;
            }

            result = pow(left->value, right->value);
            break;

        case UNARY_MINUS:
            result = left->value * -1;

        default:
            /* dummy case to silent compiler warning */
            break;
    }

    root->value = result;
    return 0;
}


Tree_node *
evaluate_ast(Tree_node *ast_root, double *result)
{
    if (!ast_root) return NULL;
    if (ast_root->type == NUMBER) return ast_root;

    Tree_node *left = evaluate_ast(ast_root->left, result);
    Tree_node *right = evaluate_ast(ast_root->right, result);

    /* Calculate the result and store inside `ast_root->value` */
    if (calculate(left, ast_root, right) == -1) {
        return NULL;
    }

    free_children_nodes(left, right);

    /* Update `result` everytime value of `ast_root` is set */
    *result = ast_root->value;
    return ast_root;
}
