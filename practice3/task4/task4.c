#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/resource.h>
#include <unistd.h>

#define COUNT1   7
#define RANGE1   49
#define COUNT2   6
#define RANGE2   36
#define CPU_LIMIT 2

static void handle_xcpu(int sig) {
    fprintf(stderr, "CPU time limit exceeded, exiting.\n");
    _exit(EXIT_FAILURE);
}

static void shuffle(int *arr, int n) {
    for (int i = 0; i < n; ++i) arr[i] = i + 1;
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

static void print_selection(int *arr, int count) {
    for (int i = 0; i < count; ++i) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main(void) {
    struct rlimit rl = { CPU_LIMIT, CPU_LIMIT };
    signal(SIGXCPU, handle_xcpu);
    if (setrlimit(RLIMIT_CPU, &rl) != 0) {
        perror("setrlimit");
        return EXIT_FAILURE;
    }

    srand((unsigned)time(NULL));

    int pool1[RANGE1];
    shuffle(pool1, RANGE1);
    printf("Lottery numbers (7 of 49): ");
    print_selection(pool1, COUNT1);

    int pool2[RANGE2];
    shuffle(pool2, RANGE2);
    printf("Lottery numbers (6 of 36): ");
    print_selection(pool2, COUNT2);

    printf("Generation complete.\n");
    return EXIT_SUCCESS;
}
