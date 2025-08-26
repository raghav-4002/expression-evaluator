#include <unistd.h>
#include <time.h>
#include <stdio.h>


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
    init_stopwatch();
}
