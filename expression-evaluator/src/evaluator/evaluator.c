#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "token.h"
#include "evaluator.h"


// TODO: Rewrite evaluator to handle unary operation


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
                fprintf(stderr, "Division by 0 is invalid\n");
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
evaluate_ast(Tree_node *ast_root)
{
    if (!ast_root) return NULL;
    if (ast_root->type == NUMBER) return ast_root;

    /*
     * If either of `left` or `right` is `NULL`,
     * this means that the previous calculation raised an
     * error. Thus, immediately returning from all recursive
     * calls is necessary.
     */

    Tree_node *left  = evaluate_ast(ast_root->left);
    if (!left) return NULL;

    Tree_node *right = evaluate_ast(ast_root->right);
    if (!right) return NULL;

    /* Store the resut of operation inside ast_root */
    if (calculate(left, ast_root, right) == -1) {
        return NULL;
    }

    return ast_root;
}
