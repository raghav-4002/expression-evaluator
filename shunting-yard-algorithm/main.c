#include <stdio.h>



#define ARRAY_SIZE 99
#define STACK_SIZE 50



char input[ARRAY_SIZE];
unsigned input_count = 0;
char postfix[ARRAY_SIZE];
unsigned post_count = 0;

char stack[STACK_SIZE];
int top = -1;



void read_input(void);



int
main(void)
{
    read_input();

    return 0;
}



void
read_input(void)
{
    printf("Enter the expression: ");
    fgets(input, ARRAY_SIZE, stdin);
}