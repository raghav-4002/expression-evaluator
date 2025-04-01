#include <stdio.h>
#include <stdlib.h>
#include <time.h>   /* Only available for POSIX Compiliant systems */


#define DIFFICULTY 0
#define GUESS 1

#define WELCOME_MSG 0
#define DIFFICULTY_MSG 1
#define DASH 2


void choose_difficulty(void);
void play(int attempts);
void handle_input(int *number, int input_type);
void print_message(int message_type);
int generate_number(void);
void clear_input_buffer(void);


int
main(void)
{
    /* seed random number generator */
    srand(time(NULL));

    int choice;
    
    print_message(WELCOME_MSG);
    
    while(1) {
        choose_difficulty();

        printf("Enter '0' to quit(else to play again): ");
        scanf("%d", &choice);

        if(choice == 0) break;
        clear_input_buffer();
    }

    return 0;
}


void
choose_difficulty(void)
{        
    int difficulty;
    
    print_message(DIFFICULTY_MSG);
    
    /*Handling invalid difficulty*/
    handle_input(&difficulty, DIFFICULTY);
    
    switch (difficulty) {
        case 1:
            play(10); // Easy: 10 attempts
            break;
        
        case 2:
            play(7); // Medium: 7 attempts
            break;
        
        case 3:
            play(5); // Hard: 5 attempts
            break;
    }
}


void
play(int attempts)
{
    int guess, rand_number = generate_number();

    print_message(DASH);

    do {
        printf("\nGuess the number (in %d attempts): ", attempts);
        handle_input(&guess, GUESS);

        if(guess > rand_number) {
            printf("You've guessed a larger number, try again...\n");
        } else if(guess < rand_number){
            printf("You've guessed a smaller number, try again...\n");
        }

        attempts--;
    } while(guess != rand_number && attempts != 0);

    if(guess == rand_number) {
        printf("\nCorrect! The number was indeed %d.\n", rand_number);
    } else {
        printf("\nYou've ran out of all the attempts.\n");
        printf("The correct number was %d\n", rand_number);
    }

    print_message(DASH);
}


/* this function might be difficult to understand -- treat it like a blackbox */
void
handle_input(int *num, int input_type)
{
    char term;
    
    if(input_type == DIFFICULTY) {
        /* only end the loop if user enters a valid difficulty */
        while(scanf("%d%c", num, &term) != 2 || term != '\n'
                || *num > 3 || *num < 1) {

            printf("Please enter a valid difficulty...\n");
            print_message(DIFFICULTY_MSG);

            if(term != '\n') clear_input_buffer();
            term = '\x1b';  /* assign escape character to term, to solve a potential bug */
        }
    }

    if(input_type == GUESS) {
        /* only end the loop if user enters a valid integer b/w 1 and 100 */
        while(scanf("%d%c", num, &term) != 2 || term != '\n'
                || *num < 1 || *num > 100) {
            printf("Please choose a valid number (between 1 and 100)...\n");
            printf("Try again: ");

            if(term != '\n') clear_input_buffer();
            term = '\x1b';
        }
    }
}


void
print_message(int message_type)
{
    if(message_type == WELCOME_MSG) {
        printf("\n------------------------------------------------------------\n");
        printf("\tWELCOME TO THE NUMBER GUESSING GAME\n");
        printf("You have to guess the correct number between 1 and 100.\n");
    }

    if(message_type == DIFFICULTY_MSG) {
        printf("\n-----------------------------------------------------------\n");
        printf("\nEasy: 10 attempts; Medium: 7 attempts; Hard: 5 attempts\n");
        printf("Choose difficulty (1: Easy, 2: Medium, 3: Hard): ");

    }

    if(message_type == DASH) {
         printf("\n------------------------------------------------------------\n");
    }
}


int
generate_number(void)
{
    return (rand() % 100) + 1;  /* generates a random number between 1 and 100 */
}


void
clear_input_buffer(void)
{
    while(getchar() != '\n')
        ;
}