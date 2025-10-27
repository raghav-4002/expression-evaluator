#ifndef TOKENS_H_
#define TOKENS_H_


typedef enum Token_type
{
    NUMBER,

    PLUS, MINUS,
    STAR, SLASH, POWER,

    UNARY_MINUS,  /* will only be used by parser and evaluator */

    LEFT_PAREN, RIGHT_PAREN,

    NIL,

} Token_type;


/* Actual `Token` datastructure */
typedef struct Token 
{
    Token_type type;
    double     value;

} Token;


#endif
