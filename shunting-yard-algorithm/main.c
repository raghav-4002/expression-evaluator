#include <stdio.h>
#include <ctype.h>



#define ARRAY_SIZE 99
#define STACK_SIZE 50



char input[ARRAY_SIZE];
unsigned input_count = 0;
char postfix[ARRAY_SIZE];
unsigned post_count = 0;

char stack[STACK_SIZE];
int top = -1;



void read_input(void);
void process_input(void);
void input_to_postfix(void);
void print_output(void);



int
main(void)
{
    read_input();
    process_input();
    print_output();

    return 0;
}



void
read_input(void)
{
    printf("Enter the expression: ");
    fgets(input, ARRAY_SIZE, stdin);
}



void
process_input(void)
{
    while(input[input_count] != '\n') {
        if(isalpha(input[input_count])) {
            input_to_postfix();
        }
    }

    /* add null character at the end */
    postfix[post_count] = '\0';
}



void
input_to_postfix(void)
{
    postfix[post_count] = input[input_count];
    input_count++;
    post_count++;    
}



void
print_output(void)
{
    post_count = 0;

    while(postfix[post_count] != '\0') {
        printf("%c", postfix[post_count]);
        post_count++;
    }
    
    printf("\n");
}