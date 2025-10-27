#include <stdio.h>

#include "input.h"
#include "lexer.h"
#include "node.h"
#include "parser.h"
#include "evaluator.h"
#include "utils.h"


int
main(void)
{
    while (1) {
        printf("\nEnter the expression: ");
        char *expression = read_from_stdin();
        if (!expression) continue;

        Token *tokens = tokenize(expression);
        if (!tokens) continue;

        size_t current = 0;
        Tree_node *ast_root = parse_expression(tokens, &current);
        if (!ast_root) continue;

        traverse_tree(ast_root);

        double result;
        evaluate_ast(ast_root, &result);
        printf("\nResult of expression: %lf\n", result);

        //TODO: Logic for freeing AST
        free(tokens);
        free(expression);
    }
}
