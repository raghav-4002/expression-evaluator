#include <sys/ioctl.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>


struct termios orig_termios;
unsigned short col_size;
unsigned short row_size;


void
unhide_cursor(void)
{
    printf("\x1b[?25h");
}


void
reset_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    unhide_cursor();
}


void
hide_cursor(void)
{
    printf("\x1b[?25l");
}


void
clear_screen(void)
{
    printf("\x1b[2J");
}


void
get_window_size(void)
{
    struct winsize ws;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    col_size = ws.ws_col;
    row_size = ws.ws_row;
}


void
enable_raw_mode(void)
{
    /* Get terminal attributes */
    tcgetattr(STDIN_FILENO, &orig_termios);

    struct termios raw = orig_termios;

    /* Enable non-cannonical mode */
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN | CS8);
	  raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
	  raw.c_oflag &= ~(OPOST);
	  raw.c_cflag |= (CS8);

    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


void
init_terminal(void)
{
    enable_raw_mode();

    get_window_size();
    clear_screen();
    hide_cursor();

    atexit(reset_terminal);
}


void
print_elapsed_time(time_t elapsed_seconds)
{
    clear_screen();
    printf("\x1b[%d;%dH", row_size / 2, col_size / 2);
    printf("%lu\n", elapsed_seconds);
}


#define ONE_SECOND 1000000000

void
complete_one_sec(struct timespec *start, struct timespec *end)
{
    long elapsed_nano_sec   = end->tv_nsec - start->tv_sec;
    long remaining_nano_sec = ONE_SECOND - elapsed_nano_sec;

    struct timespec ts = {0, remaining_nano_sec};

    nanosleep(&ts, NULL);
}


#define BUF_SIZE 1

void
process_input(char *buf)
{
    switch (buf[0]) {
        case 'q':
            exit(EXIT_SUCCESS);
            break;
    }
}


void
read_input(void)
{
    char buf[BUF_SIZE];

    int ret_val = read(STDIN_FILENO, buf, sizeof(buf));
    if (ret_val) process_input(buf);
}


void
init_stopwatch(void)
{
    struct timespec start = {0, 0};
    struct timespec end   = {0, 0};

    clock_gettime(CLOCK_MONOTONIC, &start);

    while (1) {
        read_input();
        clock_gettime(CLOCK_MONOTONIC, &end);
        print_elapsed_time(end.tv_sec - start.tv_sec);
    }
}


int
main(void)
{
    init_terminal();
    // printf("Column size: %d\nRow size: %d\n", col_size, row_size);
    init_stopwatch();
}
