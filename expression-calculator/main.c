#include <stdio.h>
#include <stdlib.h>

void
display_prompt (void)
{
  printf ("Enter the expression: ");
}

/*
 * Inputs a single line from user via stdin
 * Returns the pointer to the string.
 */
char *
input (void)
{
  char *raw_input = NULL;
  size_t n = 0;

  ssize_t line_len = getline (&raw_input, &n, stdin);

  /* Remove newline from `raw_input` */
  raw_input[line_len - 1] = '\0';

  return raw_input;
}

int
main (void)
{
  char *raw_input = NULL;

  while (1)
    {
      display_prompt ();
      raw_input = input ();

      free (raw_input);
    }

  return 0;
}
