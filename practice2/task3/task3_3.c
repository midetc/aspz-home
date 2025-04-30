#include <stdio.h>

void func() {
    int arr1[10000];
    int arr2[10000];
    printf("Top of stack after local arrays: %p\n", (void*)arr2);
}

int main() {
    int i;
    printf("Top of stack at start: %p\n", (void*)&i);
    func();
    return 0;
}

