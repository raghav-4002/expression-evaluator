#include <stdio.h>
#include <stdlib.h>

#include "input.h"


char *
read_from_stdin(void)
{
    char *line      = NULL;
    size_t line_len = 0;
    char ch;

    while ((ch = getchar()) != '\n') {
        line_len++;
        line = realloc(line, line_len * sizeof(*line));
        line[line_len - 1] = ch;
    }

    /* Add null-byte at the end */
    line = realloc(line, (line_len + 1) * sizeof(*line));
    line[line_len] = '\0';

    return line;
}
