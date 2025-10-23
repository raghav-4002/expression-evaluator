#include <stdio.h>

#include "input.h"
#include "lexer.h"
#include "node.h"
#include "parser.h"


int
main(void)
{
    while (1) {
        printf("Enter the expression: ");
        char *expression = read_from_stdin();
        if (!expression) continue;

        Token *tokens = tokenize(expression);
        if (!tokens) continue;

        Tree_node *ast_root = parse_expression(tokens, 0);
        if (!ast_root) continue;
    }
}
