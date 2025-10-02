#include <stdio.h>

#include "io-handling/input.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/node.h"
#include "parser/parser.h"


void
traverse_tree(Tree_node *ast_root)
{
    if (ast_root == NULL) return;

    Tree_node *node = ast_root;
    Node_type type = ast_root->type;

    switch (type) {
        case PLUS:
            printf("PLUS\t");
            break;
        case MINUS:
            printf("MINUS\t");
            break;
        case STAR:
            printf("STAR\t");
            break;
        case SLASH:
            printf("SLASH\t");
            break;
        case POWER:
            printf("POWER\t");
            break;
        case NUMBER:
            printf("%lf\t", node->value);
            break;
    }

    traverse_tree(node->left);
    traverse_tree(node->right);
}

int
main(void)
{
    char *string = read_from_stdin();
    Token *tokens = tokenize(string);
    size_t current = 0;
    Tree_node *ast_root = parse_expression(tokens, &current);

    printf("=====================Parsed tokens===================\n");
    for (size_t i = 0; tokens[i].type != NIL; i++) {
        switch (tokens[i].type) {
            case PLUS:
                printf("PLUS\n");
                break;

            case MINUS:
                printf("MINUS\n");
                break;

            case STAR:
                puts("STAR");
                break;

            case SLASH:
                puts("SLASH");
                break;

            case POWER:
                puts("POWER");
                break;

            case LEFT_PAREN:
                puts("LEFT_PAREN");
                break;

            case RIGHT_PAREN:
                puts("RIGHT_PAREN");
                break;

            case NUMBER:
                printf("%lf\n", tokens[i].value);
                break;
        }
    }

    printf("======================Parsed tokens==================\n");
    traverse_tree(ast_root);
}
