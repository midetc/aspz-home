#include <stdio.h>
#include <time.h>

int main(void) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (volatile long i = 0; i < 1000000000; i++);

    clock_gettime(CLOCK_MONOTONIC, &end);
    long ms = (end.tv_sec - start.tv_sec) * 1000
            + (end.tv_nsec - start.tv_nsec) / 1000000;
    printf("Elapsed: %ld ms\n", ms);
    return 0;
}
