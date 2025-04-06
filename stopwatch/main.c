#include <termios.h>
#include <unistd.h>
#include <stdlib.h>


struct {
    struct termios orig_termios;
    unsigned long seconds_elapsed;
} attributes;


void init_stopwatch(void);
void enable_raw_mode(void);
void disable_raw_mode(void);


int
main(void)
{
    init_stopwatch();
    
    return 0;
}


void
init_stopwatch(void)
{
    enable_raw_mode();

    /* Hide the cursor */
    write(STDOUT_FILENO, "\x1b[?25l", 6);

    attributes.seconds_elapsed = 0;
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