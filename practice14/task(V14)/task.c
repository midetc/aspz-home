#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

volatile sig_atomic_t ready = 0;
struct timespec start_time, end_time;

void handler(int sig) {
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    write(STDOUT_FILENO, "\nGO!\n", 5);
    ready = 1;
}

int main(void) {
    signal(SIGALRM, handler);
    srand(time(NULL));
    int delay = rand() % 4 + 2;  // випадкова затримка 2–5 с

    printf("Get ready... waiting for GO signal\n");
    alarm(delay);
    pause();

    while (!ready)
        pause();

    getchar();  // чекаємо натискання Enter
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double reaction = (end_time.tv_sec - start_time.tv_sec)
        + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("Reaction time: %.3f seconds\n", reaction);

    return 0;
}
