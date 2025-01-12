#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ASCII_ZERO 48

int play(int);
void print_message(void);
int generate_number(void);
void handle_input(int *);
void clear_buffer(void);

int main(void) 
{

  int difficulty;
  char term;
  bool continue_playing = true;

  srand(time(0)); // Seed random number generator

  print_message();

  while (continue_playing) {
    
    printf("-----------------------------------------------------------\n");
    printf("Choose difficulty (1: Easy, 2: Medium, 3: Hard): ");
    
    /*Handling invalid difficulty*/
    if (scanf("%d%c", &difficulty, &term) != 2 || term != '\n') {

      printf("\nPlease enter a valid difficulty.\n");
      clear_buffer();
      continue;

    }

    switch (difficulty) {

    case 1:
      play(10); //Easy: 10 attempts
      break;

    case 2:
      play(7); //Medium: 7 attempts
      break;

    case 3:
      play(5); //Hard: 5 attempts
      break;

    default:
      printf("Please enter a valid difficulty\n");
      continue;

    }

    printf("\nEnter '0' to quit(any other character to continue playing): ");
    continue_playing = getchar() - ASCII_ZERO; // char '0' will convert to int 0

  }

  return 0;

}



int play(int attempts) 
{

  int guess, rand_number = generate_number();

  printf("Guess the number(You have %d attempts): ", attempts);

  handle_input(&guess);

  attempts--;  //Decrement attempt after first guess

  while (guess != rand_number && attempts != 0) {

    if (guess > rand_number)
      printf("You guessed a larger number. Try again(%d attempts left): ",
             attempts);

    else if (guess < rand_number)
      printf("You guessed a smaller number. Try again(%d attempts left): ",
             attempts);

    attempts--;

    handle_input(&guess);

  }

  if (attempts == 0) { //If user runs out of all attempts

    printf("You've run out of all the attempts! The correct number was %d\n",
           rand_number);

    return NULL; //Return null for exiting the funtion

  }

  printf("Correct! The number was indeed %d\n", rand_number);

}

int generate_number(void) { return (rand() % 100 + 1); }

void print_message(void) {

  printf("\n------------------------------------------------------------\n");
  printf("\tWELCOME TO THE NUMBER GUESSING GAME\n");
  printf("You have to guess the correct number between 1 and 100.\n");
  printf("\nEasy: 10 attempts; Medium: 7 attempts; Hard: 5 attempts\n");
}

void clear_buffer(void) {

  while (getchar() != '\n')
    ;
}

void handle_input(int *num)
{
  char term;

  while(scanf("%d%c", num, &term) != 2 || term != '\n') {

    printf("Please enter a valid number: ");
    clear_buffer();
    
  }
}