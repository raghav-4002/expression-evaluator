#include <stdio.h>
#include <stdlib.h>

#include "parser/parser.h"
#include "parser/node.h"
#include "parser_helper.h"

// TODO: Handle invalid syntax and parsing errors
// TODO: Add parsing support for unary operator (- and +)

Tree_node *parse_expression(Token *tokens, size_t *current);


static Tree_node *
parse_primary(Token *tokens, size_t *current)
{
    Token current_token = tokens[*current];
    Token_type current_token_type = current_token.type;

    if (current_token_type == NUMBER) {
        /* Move to the next token */
        *current += 1;

        Tree_node *leaf = init_node(NULL, NUMBER, NULL);
        leaf->value = current_token.value;

        return leaf;
    }

    if (current_token_type == LEFT_PAREN) {
        *current += 1;

        Tree_node *expr = parse_expression(tokens, current);

        if (!expr) return NULL;

        /* If no closing parenthesis was found */
        if (tokens[*current].type != RIGHT_PAREN) {
            fprintf(stderr, "Syntax Error\n");
            return NULL;
        }

        *current += 1;

        return expr;
    }

    /*
     * If none of the above cases match,
     * it means some operator is at unexpected
     * location,
     */

    fprintf(stderr, "Syntax Error: You placed an operator at some unexpected location...\n");

    return NULL;
}


static Tree_node *
parse_exponent(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_primary(tokens, current);

    if (!expr) return NULL;

    while (match_exponent(tokens, current)) {
        Node_type operator = previous(tokens, *current);
        Tree_node *right   = parse_primary(tokens, current);

        expr = init_node(expr, operator, right);
    }

    return expr;
}


static Tree_node *
parse_factor(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_exponent(tokens, current);

    if (!expr) return NULL;

    while (match_factor(tokens, current)) {
        Node_type operator = previous(tokens, *current);
        Tree_node *right   = parse_exponent(tokens, current);

        expr = init_node(expr, operator, right);
    }

    return expr;
}


Tree_node *
parse_expression(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_factor(tokens, current);

    if (!expr) return NULL;

    while (match_additive(tokens, current)) {
        Node_type operator = previous(tokens, *current);
        Tree_node *right   = parse_factor(tokens, current);

        if (!right) return NULL;

        expr = init_node(expr, operator, right);
    }

    Token_type current_token_type = tokens[*current].type;

    /*
     * Control must leave this function only when we've reached at NIL
     * or have successfully parsed an expression inside of a pair of
     * parenthesis. If none of those cases are true, there must be some
     * syntax error.
     */

    if (current_token_type != RIGHT_PAREN && current_token_type != NIL) {
        fprintf(stderr, "Syntax Error: You might have missed some operator...\n");
        return NULL;
    }

    return expr;
}
