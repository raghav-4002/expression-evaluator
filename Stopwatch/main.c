#include <stdio.h>
#include <time.h>
#include <unistd.h>

void clrscr(void);
void format_time(time_t seconds);

int main(void)
{

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    while(1) {
        clrscr();
        
        clock_gettime(CLOCK_MONOTONIC, &end);

        format_time(end.tv_sec - start.tv_sec);

        sleep(1);
    }
    
    return 0;
}

void format_time(time_t seconds)
{
    time_t minutes, hours;

    minutes = seconds / 60;
    seconds = seconds % 60;

    hours = minutes / 60;
    minutes = minutes % 60;

    printf("Elapsed time: %.2ld:%.2ld:%.2ld\n", hours, minutes, seconds);
}

void clrscr(void)
        {printf("\033[H\033[J");}