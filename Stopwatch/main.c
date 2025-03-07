/* 
 * 'termios.h' and 'unistd.h' header files are only available 
 * in POSIX Compliant Operating Systems, like Unix and Unix-like OSes (including Linux and MacOs)
 * Thus this program won't run on Windows (as it is not POSIX Compliant).
 * In future, I will try to add compatibility for Windows also.
 */

#include <termios.h> /*Only in POSIX*/
#include <unistd.h>  /*Only in POSIX*/
#include <stdlib.h>
#include <stdio.h>


void enable_raw_mode(void);
void disable_raw_mode(void);
void clear_screen(void);
void format_time(long seconds_elapsed);


/*Hold original terminal attributes*/
struct termios orig_termios;


int main(void)
{
    /*Enable non-canonical mode*/
    enable_raw_mode();

    long seconds_elapsed = 0;   /*Holds seconds elapsed*/
    char status;                /*Used to check termination status*/

    clear_screen();

    while(1) {
        format_time(seconds_elapsed);
        
        if(read(STDIN_FILENO, &status, 1) == 1)
            break;

        seconds_elapsed++;
        clear_screen();
    }
    
    return 0;
}


void enable_raw_mode(void)
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    
    /*Enable canonical mode when the program exits*/
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;

    raw.c_lflag &= ~(ICANON | ECHO);  /*Disable canonical mode and input echoing*/
    raw.c_cc[VTIME] = 10;             /*Set waiting time for 'read()' to be 1 sec*/
    raw.c_cc[VMIN] = 0;               /*Set min characters to be read by 'read()' as 0*/

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);    
}


void disable_raw_mode(void)
{
    /*Restore the original terminal attributes*/
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}


void format_time(long seconds_elapsed)
{
    long minutes, hours;

    minutes = seconds_elapsed / 60;
    seconds_elapsed = seconds_elapsed % 60;

    hours = minutes / 60;
    minutes = minutes % 60;

    printf("======================================\n");
    printf("\tElapsed time: %.2ld:%.2ld:%.2ld\n", hours, minutes, seconds_elapsed);
    printf("======================================\n");
        
    printf("\tEnter any key to exit\n");   
}


void clear_screen(void)
{
    system("clear");
}