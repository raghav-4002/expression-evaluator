#include <stdio.h>

#include "input.h"
#include "lexer.h"
#include "node.h"
#include "parser.h"
#include "evaluator.h"
#include "utils.h"


void
cleanup(char *input, Token *tokens, Tree_node *ast_root)
{
    free(input);
    free(tokens);
    destroy_tree(ast_root);

}


int
main(void)
{
    printf("================================================================\n"
           "Supported operations:\n"
        "+ : Addition\n"
        "- : Subtraction\n"
        "* : Multiplication\n"
        "/ : Division\n"
        "^ : Exponentiation\n"
        "\nGrouping of numbers via parenthesis is also supported\n"
        "================================================================\n");

    // while (1) {
        /* Reading input */
        printf("\n> ");
        char *input = read_from_stdin();
        if (!input) return 0;//continue;

        /* Input tokenization */
        Token *tokens = tokenize(input);
        if (!tokens) {
            cleanup(input, NULL, NULL);
            return 0;
            // continue;
        }

        /* Parsing tokens */
        size_t current = 0;
        Tree_node *ast_root = parse_expression(tokens, &current);
        if (!ast_root) {
            cleanup(input, tokens, NULL);
            return 0;
            // continue;
        }

        /* Evaluation and printing of result */
        if (evaluate_ast(ast_root) == NULL) {
            cleanup(input, tokens, ast_root);
            return 0;
            // continue;
        }

        printf("%.3lf\n", ast_root->value);

        cleanup(input, tokens, ast_root);
    // }
}
