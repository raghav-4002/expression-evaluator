#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "node.h"
#include "parser_helper.h"

// TODO: Handle invalid syntax and parsing errors
// TODO: Add parsing support for unary operator (- and +) Tree_node *parse_expression(Token *tokens, size_t *current);


static Tree_node *
parse_primary(Token *tokens, size_t *current)
{
    Token current_token = tokens[*current];

    if (current_token.type == NUMBER) {
        /* Move to the next token */
        consume(tokens, current);

        /* Number nodes will always be at leaf level */
        Tree_node *leaf = init_node(NULL, NUMBER, NULL);

        if (!leaf) return NULL;

        leaf->value = current_token.value;
        return leaf;
    }

    if (current_token.type == LEFT_PAREN) {
        consume(tokens, current); /* consume ( */
        Tree_node *expr = parse_expression(tokens, current);

        if (!expr) return NULL;

        /* If no closing parenthesis was found */
        if (tokens[*current].type != RIGHT_PAREN) {
            fprintf(stderr, "( was never closed\n");
            return NULL;
        }

        consume(tokens, current);
        return expr;
    }

    /*
     * If none of the above cases match, it means that the current
     * token is some operator at an arbitrary position.
     */

    fprintf(stderr, "Syntax error\n");
    return NULL;
}


static Tree_node *
parse_exponent(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_primary(tokens, current);

    if (!expr) return NULL;

    while (match(POWER, tokens, current)) {
        Node_type operator = consume(tokens, current);
        Tree_node *right   = parse_primary(tokens, current);

        if (!right) return NULL;

        expr = init_node(expr, operator, right);
    }

    return expr;
}


static Tree_node *
parse_factor(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_exponent(tokens, current);

    if (!expr) return NULL;

    while (match(STAR, tokens, current)
        || match(SLASH, tokens, current)) {
        Node_type operator = consume(tokens, current);
        Tree_node *right   = parse_exponent(tokens, current);

        if (!right) return NULL;

        expr = init_node(expr, operator, right);
    }

    return expr;
}


Tree_node *
parse_expression(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_factor(tokens, current);

    if (!expr) return NULL;

    while (match(PLUS, tokens, current)
        || match(MINUS, tokens, current)) {
        Node_type operator = consume(tokens, current);
        Tree_node *right   = parse_factor(tokens, current);

        if (!right) return NULL;

        expr = init_node(expr, operator, right);
    }

    return expr;
}
