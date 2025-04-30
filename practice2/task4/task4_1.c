#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MSG "Function %20s: &localvar = %p\n"

static void bar_is_now_closed(void) {
    int localvar = 5;
    printf(MSG, __func__, &localvar);
    printf("Process paused, waiting for signal...\n");
    pause();
}

static void bar(void) {
    int localvar = 5;
    printf(MSG, __func__, &localvar);
    bar_is_now_closed();
}

static void foo(void) {
    int localvar = 5;
    printf(MSG, __func__, &localvar);
    bar();
}

int main(int argc, char **argv) {
    int localvar = 5;
    printf(MSG, __func__, &localvar);
    foo();
    exit(EXIT_SUCCESS);
}

