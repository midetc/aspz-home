#include <stdio.h>

int main(void) {
    int i;
    printf("The stack top is near %p\n", (void*)&i);
    return 0;
}

