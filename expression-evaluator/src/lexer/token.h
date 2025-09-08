#ifndef TOKENS_H_
#define TOKENS_H_


typedef enum Token_type
{
    NUMBER,

    PLUS, MINUS,
    STAR, SLASH, POWER,

    LEFT_PAREN, RIGHT_PAREN,

    NIL,

} Token_type;


/* Actual `Token` datastructure */
typedef struct Token 
{
    Token_type type;
    double     number;

} Token;


#endif
