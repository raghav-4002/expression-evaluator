#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "lexer.h"
#include "token.h"
#include "lexer_helper.h"


/*
 * @brief : Adds literal value of argument into token
            of type `COMMAND`.
 * @param : A pointer to `struct Parameters`.
 */
void
add_number(struct Lexer_obj *lexer_obj)
{
    char *string     = lexer_obj->source;
    size_t start     = lexer_obj->start;
    size_t end       = lexer_obj->current;
    size_t cur_index = lexer_obj->arr_size - 1;

    lexer_obj->tokens[cur_index].value = extract_number(string, start, end);
}


/*
 * @brief : Adds a token into `tokens` array.
 * @param : A pointer to `struct Parameters`.
            `Token_type` enum Member.
 * @return: `0` on success; `-1` on failure.
 */
int
add_token(struct Lexer_obj *lexer_obj, Token_type type)
{
    Token *tokens = lexer_obj->tokens;

    /* Add space for one more token */
    lexer_obj->arr_size += 1;
    size_t arr_size       = lexer_obj->arr_size;
    size_t cur_index      = arr_size - 1;

    /* Resize array */
    tokens = realloc(tokens, arr_size * sizeof(*tokens));

    //FIX: Change error hanlding method for realloc
    if (!tokens) {
        perror(NULL);
        lexer_obj->arr_size -= 1;  /* reset array size */
        return -1;
    }

    Token *cur_token = &tokens[cur_index];
    init_token(cur_token, type);

    lexer_obj->tokens = tokens;

    if (type == NUMBER) {
        add_number(lexer_obj);
    }

    return 0;
}


/*
 * @brief : Tokenizes a lexeme of type `NUMBER`
 * @param : A pointer to `struct Parameters`.
 * @return: `0` on success; `-1` on failure.
 */
int
handle_number(struct Lexer_obj *lexer_obj)
{
    char current_char = lexer_obj->source[lexer_obj->current];
    bool decimal_already_covered = false;

    /* Move ahead until some non-numeric character is not found */
    while ((current_char >= '0' && current_char <= '9')
        || current_char == '.') {

        if (current_char == '.' ) {
            /* . is encountered but there's already a decimal */
            if (decimal_already_covered) {
                fprintf(stderr, "Syntax error: Encountered an extra .\n");
                return -1;
            }

            decimal_already_covered = true;
        }

        advance_current(lexer_obj);
        current_char = lexer_obj->source[lexer_obj->current];
    }

    int err_return = add_token(lexer_obj, NUMBER);
    return err_return;
}


/*
 * @brief : Recognises the current lexeme.
 * @param : A pointer to `struct Parameters`.
 * @return: `0` on success; `-1` on failure
 */
int
scan_token(struct Lexer_obj *lexer_obj)
{
    char c = advance_current(lexer_obj);

    int err_return = 0;

    switch (c) {
        case '+':
            err_return = add_token(lexer_obj, PLUS);
            break;
        case '-':
            err_return = add_token(lexer_obj, MINUS);
            break;
        case '*':
            err_return = add_token(lexer_obj, STAR);
            break;
        case '/':
            err_return = add_token(lexer_obj, SLASH);
            break;
        case '^':
            err_return = add_token(lexer_obj, POWER);
            break;
        case '(':
            err_return = add_token(lexer_obj, LEFT_PAREN);
            break;
        case ')':
            err_return = add_token(lexer_obj, RIGHT_PAREN);
        case ' ': case '\n': case '\t':
            break;

        default:
            /* Number tokens */
            if ((c >= '0' && c <= '9') || c == '.') {
                err_return = handle_number(lexer_obj);
                break;
            }
 
            fprintf(stderr, "Unrecognised token: '%c'\n", c);
            err_return = -1;
            break;
    }

    if (err_return == -1) return -1;

    return 0;
}


/*
 * @brief : Tokenizes an input string; stops when encounters `\0`
 * @param : An input string
 * @return: An array of type `Token`; last element is type `NIL`
 *          `NULL` on failure
 *          The caller must free the array returned
 */
Token *
tokenize(char *input)
{
    /*
     * A pointer to structure `Parameters`

     * Members of `struct Parameters`

     * `Token *tokens`  : a pointer to an array of tokens.
     * `size_t arr_size`: represents size of the tokens array.

     * `char *source`   : source string to be tokenized.
     * `size_t start`   : an index pointing to the head of the 
                          lexeme being considered.
     * `size_t current` : an index pointing to the current character
                          being considered.
     */
    struct Lexer_obj *lexer_obj = malloc(sizeof(*lexer_obj));

    if (!lexer_obj) {
        perror(NULL);
        return NULL;
    }

    init_parameters(lexer_obj, input);

    int err_return = 0;

    while (!current_is_at_end(lexer_obj)) {
        /* Move to the next lexeme */
        lexer_obj->start = lexer_obj->current;
        err_return        = scan_token(lexer_obj);

        if (err_return == -1) {
            free_tokens_on_error(lexer_obj);
            return NULL;
        }
    }

    /* Add `NIL` as last token */
    err_return = add_token(lexer_obj, NIL);

    if (err_return == -1) {
        free_tokens_on_error(lexer_obj);
        return NULL;
    }

    return lexer_obj->tokens;
}
