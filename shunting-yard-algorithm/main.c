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
void input_to_stack(void);
void empty_stack(void);
void stack_to_post(void);
void handle_operand(void);



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
            input_count++;
            continue;
        }

        if(input[input_count] == '(') {
            input_to_stack();
            input_count++;
            continue;
        }

        if(input[input_count] == ')') {
            empty_stack();
            input_count++;
            continue;
        }

        handle_operand();
    }

    /* add null character at the end */
    postfix[post_count] = '\0';
}



void
input_to_postfix(void)
{
    postfix[post_count] = input[input_count];
    post_count++;    
}



void 
input_to_stack(void)
{
    top++;
    stack[top] = input[input_count];
}



void
empty_stack(void)
{
    while(stack[top] != '(') {
        stack_to_post();
    }
    top--;
}



void
stack_to_post(void)
{
    postfix[post_count] = stack[top];
    post_count++;
    top--;
}



void
handle_operand(void)
{

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