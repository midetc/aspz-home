#include <stdio.h>
#include <stdlib.h>

int main() {
    void *block1 = realloc(NULL, 16);
    if (block1) {
        printf("realloc(NULL, 16) succeeded: block1 = %p\n", block1);
    } else {
        printf("realloc(NULL, 16) failed\n");
    }

    void *block2 = malloc(32);
    if (!block2) {
        perror("malloc failed");
        return 1;
    }

    printf("Allocated block2: %p\n", block2);

    void *block3 = realloc(block2, 0);
    printf("realloc(block2, 0) returned: block3 = %p\n", block3);

    if (block3) {
        free(block3);
    }

    return 0;
}
