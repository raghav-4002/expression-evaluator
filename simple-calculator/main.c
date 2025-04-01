#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void print_message(void);
void calculate(char);
void clear_buffer(void);
void handle_input(double *, double *);

int main(void) {

  char operation;

  print_message();

  while (true) {

    printf("--------------------------------------\n");
    printf("'+' for Addition\n'-' for Subtraction\n");
    printf("'*' for Multiplication\n'/' for Division\n");
    printf("'^' for Exponentiation\n'0' to Quit\n");
    printf("--------------------------------------\n");

    printf("Choose the operation: ");
    operation = getchar();

    if (operation == '0')
      break;

    switch (operation) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
      calculate(operation);
      break;

    default:
      printf("Please choose a valid operation.\n");
      clear_buffer();
      break;
    }

  }

  return 0;
}

void print_message(void) {
  printf("\n--------------------------------------\n");
  printf("\tSIMPLE CALCULATOR\n");
  printf("--------------------------------------\n");
}


void calculate(char operation) {

  double first_num, second_num, result;

  printf("Enter the numbers: ");
  handle_input(&first_num, &second_num);

  /*Handling errors for both division and exponentiation*/
  if (second_num == 0) {
    if (operation == '/') {
      printf("Division by zero is not possible.\n");
      return;
    }
    if (operation == '^' && first_num == 0) {
      printf("Zero to the power of zero isn't defined.\n");
      return;
    }
  }

  /*Performing the operations*/
  switch (operation) {
  case '+':
    result = first_num + second_num;
    break;

  case '-':
    result = first_num - second_num;
    break;

  case '*':
    result = first_num * second_num;
    break;

  case '/':
    result = first_num / second_num;
    break;

  case '^':
    result = pow(first_num, second_num);
    break;
  }

  printf("\nThe result of operation is: %.2lf\n", result);
}


void clear_buffer(void) {
  while (getchar() != '\n')
    ;
}

void handle_input(double *num1, double *num2) {

    char ch;

    /*Looping until the user enters valid values*/
    while(scanf("%lf%lf%c", num1, num2, &ch) != 3 || ch != '\n') {
        printf("Please enter valid numbers: ");
        clear_buffer();
    }
}