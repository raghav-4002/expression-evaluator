#include <bits/time.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>


/* ========== Global variables ========== */

struct Term_parameters {
    struct termios orig_termios;
    unsigned short col_size;
    unsigned short row_size;
};

struct Term_parameters term_parameters;


typedef enum {
    RUNNING,
    PAUSED,

} Running_status;


struct Elapsed_time {
    long sec;
    long min;
    long hour;
};


/* ========== Helper functions ========== */

void
unhide_cursor(void)
{
    printf("\x1b[?25h");
}


void
reset_terminal(void)
{
    /* Disable raw mode */
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &(term_parameters.orig_termios));

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


/* ========== Terminal-related functions ========== */
void
get_window_size(void)
{
    struct winsize ws;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    term_parameters.col_size = ws.ws_col;
    term_parameters.row_size = ws.ws_row;
}


void
enable_raw_mode(void)
{
    /* Get terminal attributes */
    tcgetattr(STDIN_FILENO, &(term_parameters.orig_termios));

    struct termios raw = term_parameters.orig_termios;

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
recenter_cursor(unsigned short row_pos, unsigned short col_pos)
{
    printf("\x1b[%d;%dH", row_pos, col_pos);
}


/* ========== Stopwatch-related funcitons ========== */

struct Elapsed_time
calculate_elapsed_time(time_t elapsed_seconds)
{
    long min = elapsed_seconds / 60;
    long hour = min / 60;

    long sec = elapsed_seconds % 60;
    min %= 60;

    struct Elapsed_time time = {sec, min, hour};

    return time;
}


void
print_elapsed_time(time_t elapsed_seconds)
{
    recenter_cursor(term_parameters.row_size / 2, term_parameters.col_size / 2);

    struct Elapsed_time time = calculate_elapsed_time(elapsed_seconds);

    printf("%.2ld:%.2ld:%.2ld", time.hour, time.min, time.sec);
    fflush(stdout);
}


void
print_quit_msg(void)
{
    recenter_cursor((term_parameters.row_size / 2) + 1, term_parameters.col_size / 2);
    printf("q: To quit");
    fflush(stdout);
}


void
print_status_msg(Running_status status)
{
    recenter_cursor((term_parameters.row_size / 2) + 2, term_parameters.col_size / 2);

    // TODO: do something smarter instead of this innocent if-else clause
    if (status == PAUSED) {
        printf("space: To continue");
    }
    else {
        printf("space: To pause");
    }
    fflush(stdout);
}


void
display_output(time_t elapsed_seconds, Running_status status)
{
    // TODO: Replace calls to `printf` with `write`
    clear_screen();
    print_elapsed_time(elapsed_seconds);
    print_quit_msg();
    print_status_msg(status);
}


void
flip_running_status(Running_status *status)
{
    if (*status == RUNNING) {
        *status = PAUSED;
    }

    else if (*status == PAUSED) {
        *status = RUNNING;
    }
}


#define BUF_SIZE 1

bool
process_input(char *buf)
{
    switch (buf[0]) {
        case 'q':
            exit(EXIT_SUCCESS);
            break;

        case ' ':
            return true;
            break;
    }

    return false;
}


int
read_input(char **buf)
{
    return read(STDIN_FILENO, *buf, BUF_SIZE);
}


void
reset_start(struct timespec *start)
{
    clock_gettime(CLOCK_MONOTONIC, start);
}


void
update_end(struct timespec *end)
{
    clock_gettime(CLOCK_MONOTONIC, end);
}


void
init_stopwatch(void)
{
    /* Time keeping variables */
    struct timespec start;
    struct timespec end;

    Running_status status  = RUNNING;
    time_t elapsed_seconds = 0;

    char *buf = malloc(BUF_SIZE * sizeof(*buf));

    /* Initialize the starting clock */
    reset_start(&start);

    while (1) {
        display_output(elapsed_seconds, status);
        int bytes_read = read_input(&buf);

        if (bytes_read) {
            bool need_to_flip_status = process_input(buf);

            if (need_to_flip_status) {
                flip_running_status(&status);
                reset_start(&start);
            }
        }

        update_end(&end);

        /* After every 1 second, increment elapsed_seconds and reset start */
        if (status == RUNNING && end.tv_sec - start.tv_sec == 1) {
            elapsed_seconds++;
            reset_start(&start);
        }
    }
}


int
main(void)
{
    init_terminal();
    init_stopwatch();
}
