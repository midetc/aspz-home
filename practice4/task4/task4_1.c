#include <stdio.h>
#include <stdlib.h>

int main() {
    void *memory = NULL;

    for (int i = 0; i < 3; ++i) {
        if (!memory)
            memory = malloc(10);
        if (!memory) {
            perror("Memory allocation failed");
            return 1;
        }

        printf("Iteration %d: memory = %p\n", i, memory);
        free(memory);
    }

    return 0;
}
