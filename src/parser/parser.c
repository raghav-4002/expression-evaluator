#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "node.h"
#include "parser_helper.h"
#include "token.h"


/* Stack to match an opening parenthesis with closed one */
Paren_stack *paren_stack = NULL;


static Tree_node *parse_expression(Token *tokens, size_t *current);


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
        push_paren(&paren_stack);
        consume(tokens, current); /* consume ( */
        Tree_node *expr = parse_expression(tokens, current);

        if (!expr) return NULL;

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
parse_unary(Token *tokens, size_t *current)
{
    if (expect(PLUS, tokens, current)
     || expect(MINUS, tokens, current)) {

        /* Only handle Unary minus because unary plus has no effect */
        if (consume(tokens, current) == MINUS) {
            Tree_node *child = parse_unary(tokens, current);

            /* Unary node will only have a left child */
            Tree_node *expr  = init_node(child, UNARY_MINUS, NULL);
            return expr;
        }
    }

    return parse_primary(tokens, current);
}


static Tree_node *
parse_exponent(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_unary(tokens, current);

    if (!expr) return NULL;

    while (expect(POWER, tokens, current)) {
        Node_type operator = consume(tokens, current);
        Tree_node *right   = parse_unary(tokens, current);

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

    while (expect(STAR, tokens, current)
        || expect(SLASH, tokens, current)) {

        Node_type operator = consume(tokens, current);
        Tree_node *right   = parse_exponent(tokens, current);

        if (!right) return NULL;

        expr = init_node(expr, operator, right);
    }

    return expr;
}


static Tree_node *
parse_expression(Token *tokens, size_t *current)
{
    Tree_node *expr = parse_factor(tokens, current);

    if (!expr) {
        wrap_up_parser(expr, &paren_stack);
        return NULL;
    }

    while (expect(PLUS, tokens, current)
        || expect(MINUS, tokens, current)) {

        Node_type operator = consume(tokens, current);
        Tree_node *right   = parse_factor(tokens, current);

        if (!right) {
            wrap_up_parser(expr, &paren_stack);
            return NULL;
        }

        expr = init_node(expr, operator, right);
    }

    if (expect(RIGHT_PAREN, tokens, current)) {
        /* 
         * Current token is closing parenthesis but no opening parenthesis
         * was found => Unmatched ) error
         */

        if (!paren_stack) {
            fprintf(stderr, "Syntax Error: Unmatched )\n");
            wrap_up_parser(expr, &paren_stack);

            return NULL;
        }

        /* Pop the matching opening parenthesis */
        pop_paren(&paren_stack);
        return expr;
    }

    else {
        if (paren_stack) {
            fprintf(stderr, "Syntax Error: ( was never closed\n");
            wrap_up_parser(expr, &paren_stack);

            return NULL;
        }

        return expr;
    }
}


Tree_node *
parse_tokens(Token *tokens)
{
    size_t current = 0;

    Tree_node *expr = parse_expression(tokens, &current);

    /* Error has been printed */
    if (!expr) return NULL;

    /* If not all tokens are parsed, throw an error */
    if (tokens[current].type != NIL) {
        fprintf(stderr, "Syntax error\n");
        return NULL;
    }

    return expr;
}
