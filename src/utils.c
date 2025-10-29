#include <stdio.h>

#include "node.h"
#include "utils.h"
#include "token.h"


void
destroy_tree(Tree_node *root)
{
    if (!root) return;

    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}


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

        default:  /* To get rid of compiler warning */
            break;
    }

    traverse_tree(node->left);
    traverse_tree(node->right);
}
