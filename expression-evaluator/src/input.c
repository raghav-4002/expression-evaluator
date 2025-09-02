#include <stdio.h>
#include <stdlib.h>

#include "input.h"

/*
 * @brief: Replaces newline with null-byte
 * @param: User input string and length of the string
 */
void
remove_newline(char *user_input, ssize_t line_len)
{
    user_input[line_len - 1] = '\0';
}


/*========== Public Interface ==========*/

/*
 * @brief:  Takes input from stdin
 * @return: Returns the inputted string
 */
char *
get_user_input(void)
{
    char *user_input = NULL;
    size_t n         = 0;

    ssize_t line_len = getline(&user_input, &n, stdin);

    /* In case of error */
    if(line_len == -1) 
    {
        free(user_input);
        return NULL;
    }

    /* Remove the trailing newline */
    remove_newline(user_input, line_len);

    return user_input;
}
