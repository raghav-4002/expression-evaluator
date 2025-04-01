#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define DIFFICULTY 0
#define GUESS 1

#define WELCOME_MSG 0
#define DIFFICULTY_MSG 1
#define PLAYIN_MSG 2


void print_message(int message_type);
void choose_difficulty(void);
void play(int attempts);
int generate_number(void);
void handle_input(int *number, int input_type);
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

    print_message(PLAYIN_MSG);

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
        // printf("It took you %d attempts to guess the correct number\n", attempts + 1);
    } else {
    printf("\nYou've ran out of all the attempts.\n");
    printf("The correct number was %d\n", rand_number);
    }

    print_message(PLAYIN_MSG);
}


/*Handle invalid input*/
void
handle_input(int *num, int input_type)
{
    char term;
    
    if(input_type == DIFFICULTY) {
        while(scanf("%d%c", num, &term) != 2 || term != '\n'
                || *num > 3 || *num < 1) {

            printf("Please enter a valid difficulty...\n");
            print_message(DIFFICULTY_MSG);

            if(term != '\n') clear_input_buffer();
            term = '\x1b';
        }
    }

    if(input_type == GUESS) {
        while(scanf("%d%c", num, &term) != 2 || term != '\n'
                || *num < 1 || *num > 100) {
            printf("Please choose a valid number...\n");
            printf("Try again: ");
            clear_input_buffer();
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
        printf("\nEasy: 10 attempts; Medium: 7 attempts; Hard: 5 attempts\n");
    }

    if(message_type == DIFFICULTY_MSG) {
        printf("\n-----------------------------------------------------------\n");
        printf("Choose difficulty (1: Easy, 2: Medium, 3: Hard): ");

    }

    if(message_type == PLAYIN_MSG) {
         printf("\n------------------------------------------------------------\n");
    }
}


/*Generate a random number between 1 and 100*/
int
generate_number(void)
{
    return (rand() % 100) + 1;
}


/*Clear input buffer*/
void
clear_input_buffer(void)
{
    while(getchar() != '\n')
        ;
}