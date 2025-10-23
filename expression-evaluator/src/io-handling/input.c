#include <stdio.h>
#include <stdlib.h>

#include "input.h"


/*
 * Reads a line from standard input.
 * Returns NULL on failure else the line read.
 * The caller must free the line that's been read.
 */
char *
read_from_stdin(void)
{
    char *line      = NULL;
    size_t line_len = 0;
    char ch;
    char *temp;

    while ((ch = getchar()) != '\n') {
        line_len++;
        temp = realloc(line, line_len * sizeof(*line));

        /* On error, free the original block of memory before returning NULL */
        if (!temp) {
            perror(NULL);
            free(line);
            return NULL;
        }

        line = temp;
        line[line_len - 1] = ch;
    }

    /* Add null-byte at the end */
    temp = realloc(line, (line_len + 1) * sizeof(*line));

    if (!temp) {
        perror(NULL);
        free(line);
        return NULL;
    }

    line = temp;
    line[line_len] = '\0';

    return line;
}
