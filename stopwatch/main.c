#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>


struct termios orig_termios;


void
setup_terminal(void)
{
    /* Get terminal attributes */
    tcgetattr(STDIN_FILENO, &orig_termios);

    struct termios raw = orig_termios;

    /* Enable non-cannonical mode */
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN | CS8);
	  raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
	  raw.c_oflag &= ~(OPOST);
	  raw.c_cflag |= (CS8);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


void
reset_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}


void
print_elapsed_time(time_t elapsed_seconds)
{
    printf("%lu\n", elapsed_seconds);
}


void
init_stopwatch(void)
{
    struct timespec start = {0, 0};
    struct timespec end   = {0, 0};

    clock_gettime(CLOCK_MONOTONIC, &start);

    while (1) {
        sleep(1);
        clock_gettime(CLOCK_MONOTONIC, &end);
        print_elapsed_time(end.tv_sec - start.tv_sec);
    }
}


int
main(void)
{
    setup_terminal();
    atexit(reset_terminal);
    init_stopwatch();
}
