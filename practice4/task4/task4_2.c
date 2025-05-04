#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void *block = malloc(16);
    if (!block) {
        perror("Allocation error");
        return 1;
    }

    strcpy(block, "Hello!");
    printf("Before free: %s (block = %p)\n", (char *)block, block);

    free(block);

    printf("After free, block still points to: %p\n", block);
    printf("After free: %s\n", (char *)block);

    return 0;
}
