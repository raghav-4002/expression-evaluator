#include <stdlib.h>
#include <string.h>

#include "lexer_helper.h"
#include "utils.h"


void
init_parameters(struct Lexer_obj *lexer_obj, char *input)
{
    lexer_obj->tokens    = NULL;
    lexer_obj->arr_size  = 0;

    lexer_obj->source    = input;
    lexer_obj->start     = 0;
    lexer_obj->current   = 0;
}


/*
 * @brief : Tells whether `current` points at the end ('\0')
 * @return: `true`, if yes
 */
bool
current_is_at_end(struct Lexer_obj *lexer_obj)
{
    char *source   = lexer_obj->source;
    size_t current = lexer_obj->current;

    if (source[current] == '\0') return true;

    return false;
}


/* 
 * @brief : Advances `current`
 * @return: Character previous to `current`
 */
char
advance_current(struct Lexer_obj *lexer_obj)
{
    lexer_obj->current += 1;

    size_t current = lexer_obj->current;
    char  *source  = lexer_obj->source;

    return source[current - 1];
}


/* 
 * Returns `true` if the next char to `current` is `expected`.
 * Else returns `false`.
 */
bool
match(struct Lexer_obj *lexer_obj, char expected)
{
    char *source   = lexer_obj->source;
    size_t current = lexer_obj->current;

    if (source[current] == expected) return true;

    return false;
}


/* Initializes a `token` with default values. */
void
init_token(Token *token, Token_type type)
{
    token->type          = type;
    token->value         = 0;
}


/*
 * @brief : Creates a substring from a given string
 * @param : Pointer to original string; starting and terminating index of
 *          substring
 * @return: A `malloc`d array of substring
 */
char *
create_substring(char *string, size_t start, size_t end)
{
    /* Add `1` for null-byte */
    size_t buf_size = (end - start) + 1;
    char *substring = malloc(buf_size * sizeof(*substring));

    if (!substring) return NULL;

    string += start;  /* `string` ptr points to start of substring */
    memcpy(substring, string, buf_size - 1);
    substring[buf_size - 1] = '\0';

    return substring;
}


/*
 * @brief : Frees memory allocated to tokens if error occurs.
 * @param : A pointer to `struct Parameters`.
 */
void
free_lexer_obj(struct Lexer_obj *lexer_obj)
{
    Token *tokens       = lexer_obj->tokens;
    free(tokens);
    free(lexer_obj);
}


double
extract_number(char *string, size_t start, size_t end)
{
    size_t buf_size = end - start + 1;
    char buf[buf_size];

    string += start;
    memcpy(buf, string, buf_size - 1);
    buf[buf_size - 1] = '\0';

    return atof(buf);
}
