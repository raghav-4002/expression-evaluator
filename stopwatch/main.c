#include <asm-generic/ioctls.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>


struct {
    struct termios orig_termios;
    unsigned long seconds_elapsed;
    int window_length, window_width;
} attributes;


void init_stopwatch(void);
void display_time(void);
void get_window_size(void);
void enable_raw_mode(void);
void disable_raw_mode(void);


int
main(void)
{
    init_stopwatch();

    while(1) {
        display_time();
    }
    
    return 0;
}


void
init_stopwatch(void)
{
    enable_raw_mode();
    get_window_size();

    /* clear the screen */
    write(STDOUT_FILENO, "\x1b[2J", 4);
    /* Hide the cursor */
    write(STDOUT_FILENO, "\x1b[?25l", 6);

    /* initialize the elapsed seconds with 0 */
    attributes.seconds_elapsed = 0;
}


void
get_window_size(void)
{
    struct winsize ws;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    attributes.window_length = ws.ws_row;
    attributes.window_width = ws.ws_col;
}


void
display_time(void)
{
    /* set cursor position */
    char pos[32];
    size_t len;
    len = snprintf(pos, sizeof(pos), "\x1b[%d;%dH", 
                    attributes.window_length / 2, attributes.window_width / 2);
    write(STDOUT_FILENO, pos, len);

    /* Clear the screen */
    write(STDOUT_FILENO, "\x1b[K", 3);

    unsigned long hours, minutes;

    minutes = attributes.seconds_elapsed / 60;
    attributes.seconds_elapsed %= 60;

    hours = minutes / 60;
    minutes %= 60;

    char display_string[32];
    size_t string_len;

    string_len = snprintf(display_string, sizeof(display_string), "%.2lu:%.2lu:%.2lu", 
                    hours, minutes, attributes.seconds_elapsed);

    /* write the time */
    write(STDOUT_FILENO, display_string, string_len);
}


void
enable_raw_mode(void)
{
    tcgetattr(STDIN_FILENO, &attributes.orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = attributes.orig_termios;

    /* enable raw mode */
    raw.c_lflag &= ~(ECHO | ICANON);

    /* set updated terminal settings */
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


void
disable_raw_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes.orig_termios);

    /* Unhide the cursor */
    write(STDOUT_FILENO, "\x1b[?25h", 6);
}