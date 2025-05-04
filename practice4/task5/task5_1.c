#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t huge_alloc = 1024L * 1024L * 1024L * 1024L; // 1 TB
    void *buffer = malloc(1024);

    if (!buffer) {
        perror("Failed to allocate initial memory");
        return 1;
    }

    printf("Successfully allocated initial memory: %p\n", buffer);

    void *resized = realloc(buffer, huge_alloc);

    if (!resized) {
        perror("Unable to reallocate to larger size");
        printf("Original buffer remains valid: %p\n", buffer);
    } else {
        buffer = resized;
        printf("Reallocation successful, new pointer: %p\n", buffer);

        memset(buffer, 0, huge_alloc);
        printf("Large memory block zeroed out\n");
    }

    free(buffer);
    return 0;
}
