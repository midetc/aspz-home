#include <stdio.h>
#include <stdlib.h>

static void probe_stack(int level) {
    volatile char marker[128];
    printf("Stack level: %d (marker at %p)\n", level, (void*)&marker);
    probe_stack(level + 1);
}

int main(void) {
    puts("Stack probing started...");
    probe_stack(1);
    return EXIT_SUCCESS;
}
