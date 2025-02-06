/*clear screen using printf("\033[H\033[J");*/

#include <stdio.h>
#include <time.h>

void format_time(time_t seconds);

int main(void)
{

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    printf("Time has started...\n");
    printf("\nEnter any character to quit: ");
    getchar();

    clock_gettime(CLOCK_MONOTONIC, &end);

    /*Format the elapsed time*/
    format_time(end.tv_sec - start.tv_sec);

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