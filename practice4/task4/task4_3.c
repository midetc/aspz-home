#include <stdio.h>
#include <stdlib.h>

int main() {
    void *chunk = NULL;

    for (int pass = 0; pass < 3; ++pass) {
        if (!chunk)
            chunk = malloc(10);
        if (!chunk) {
            perror("Failed to allocate memory");
            return 1;
        }

        printf("Pass %d: chunk = %p\n", pass, chunk);
        free(chunk);
        chunk = NULL;
    }

    return 0;
}
