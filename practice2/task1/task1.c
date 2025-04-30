#include <stdio.h>
#include <time.h>

int main() {
    time_t max_time = (time_t)((1ULL << (sizeof(time_t) * 8 - 1)) - 1ULL);
    printf("Max time_t value: %ld\n", (long)max_time);
    printf("Date and time: %s", ctime(&max_time));

    time_t overflow_time = max_time + 1;
    printf("After overflow: %s", ctime(&overflow_time));

    return 0;
}

