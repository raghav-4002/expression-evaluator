#include "utils.h"
#include "lexer/token.h"


void
free_tokens(Token *tokens)
{
    free(tokens);
}
