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
    printf("\nEnter the expression: ");
    char *expression = read_from_stdin();
    if (!expression) return 0;

    Token *tokens = tokenize(expression);
    if (!tokens) {
        free(expression);
        return 0;
    }

    size_t current = 0;
    Tree_node *ast_root = parse_expression(tokens, &current);
    if (!ast_root) {
        free(expression);
        free(tokens);
        return 0;
    }

    traverse_tree(ast_root);

    if (evaluate_ast(ast_root) == NULL) {
        free(expression);
        free(tokens);
        return 0;
    }

    printf("\nResult of expression: %lf\n", ast_root->value);

    free(expression);
    free(tokens);
    free(ast_root);
}
