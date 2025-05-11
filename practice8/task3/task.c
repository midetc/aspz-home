#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

int compare_ints(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

void generate_increasing(int *arr, size_t n) {
    for (size_t i = 0; i < n; ++i)
        arr[i] = (int)i;
}

void generate_decreasing(int *arr, size_t n) {
    for (size_t i = 0; i < n; ++i)
        arr[i] = (int)(n - i);
}

void generate_constant(int *arr, size_t n) {
    for (size_t i = 0; i < n; ++i)
        arr[i] = 42;
}

void generate_random(int *arr, size_t n) {
    for (size_t i = 0; i < n; ++i)
        arr[i] = rand();
}

int is_sorted(int *arr, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        if (arr[i-1] > arr[i])
            return 0;
    }
    return 1;
}

long timed_qsort(int *arr, size_t n) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    qsort(arr, n, sizeof(int), compare_ints);
    gettimeofday(&end, NULL);
    long sec = end.tv_sec - start.tv_sec;
    long usec = end.tv_usec - start.tv_usec;
    return sec * 1000000 + usec;
}

int main(void) {
    size_t sizes[] = {10000, 20000, 50000, 100000};
    const char *names[] = {"increasing", "decreasing", "constant", "random"};
    void (*gens[])(int*, size_t) = {generate_increasing, generate_decreasing, generate_constant, generate_random};
    size_t types = sizeof(gens) / sizeof(gens[0]);
    srand(0);

    printf("size,type,time_us,correct\n");
    for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); ++i) {
        size_t n = sizes[i];
        int *arr = malloc(n * sizeof(int));
        int *copy = malloc(n * sizeof(int));
        for (size_t t = 0; t < types; ++t) {
            gens[t](arr, n);
            memcpy(copy, arr, n * sizeof(int));
            long t_us = timed_qsort(arr, n);
            int correct = is_sorted(arr, n);
            printf("%zu,%s,%ld,%d\n", n, names[t], t_us, correct);
        }
        free(arr);
        free(copy);
    }
    return 0;
}
