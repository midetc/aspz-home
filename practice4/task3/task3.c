#include <stdio.h>
#include <stdlib.h>

int main() {
    void *allocated = malloc(0);

    if (!allocated) {
        printf("Результат malloc(0): NULL\n");
    } else {
        printf("Результат malloc(0): вказівник %p\n", allocated);
        free(allocated);
    }

    return 0;
}
