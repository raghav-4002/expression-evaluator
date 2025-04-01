#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIFFICULTY 0
#define GUESS 1

#define ASCII_ZERO 48 // To check if the user wants to play again


void print_message(void);
void choose_difficulty(void);
void play(int);
int generate_number(void);
void handle_input(int *, int input_type);
void clear_input_buffer(void);


int
main(void)
{
    /* seed random number generator */
    srand(time(NULL));

    int choice;
    
    while(1) {
        print_message();
        choose_difficulty();

        printf("Enter '0' to quit(else to play again): ");
        scanf("%d", &choice);

        if(choice == 0) break;
    }

    return 0;
}


void print_message(void)
{
    printf("\n------------------------------------------------------------\n");
    printf("\tWELCOME TO THE NUMBER GUESSING GAME\n");
    printf("You have to guess the correct number between 1 and 100.\n");
    printf("\nEasy: 10 attempts; Medium: 7 attempts; Hard: 5 attempts\n");
}


void
choose_difficulty(void)
{        
        int difficulty;
        printf("-----------------------------------------------------------\n");
        printf("Choose difficulty (1: Easy, 2: Medium, 3: Hard): ");
    
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


// void play(int attempts)
// {
//     int guess, rand_number = generate_number();

//     printf("Guess the number(You have %d attempts): ", attempts);

//     handle_input(&guess);

//     attempts--; // Decrement attempt after first guess

//     while (guess != rand_number && attempts != 0) {

//         if (guess > rand_number)
//             printf("You guessed a larger number. Try again(%d attempts left): ",
//                 attempts);

//         else if (guess < rand_number)
//             printf("You guessed a smaller number. Try again(%d attempts left): ",
//                 attempts);

//         attempts--;

//         handle_input(&guess);
//     }

//     if (attempts == 0 && guess != rand_number) { // If user runs out of all attempts
//         printf("You've run out of all the attempts! The correct number was %d\n",
//             rand_number);

//         return;
//     }

//     /*If attempts != 0*/
//     printf("Correct! The number was indeed %d\n", rand_number);
// }

void
play(int a)
{
    printf("Playing");
}


/*Generate a random number between 1 and 100*/
int generate_number(void) { return (rand() % 100 + 1); }


/*Handle invalid input*/
void handle_input(int *num, int input_type)
{
    char term;
    
    if(input_type == DIFFICULTY) {
        while(scanf("%d%c", num, &term) != 2 || term != '\n'
                || *num > 3 || *num < 1) {

            printf("Please choose a valid difficulty...\n");
            printf("Try again: ");

            if(term != '\n') {
                clear_input_buffer();
            }
            term = '\x1b';
        }
        return;
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


/*Clear input buffer*/
void
clear_input_buffer(void)
{
    while(getchar() != '\n')
        ;
}