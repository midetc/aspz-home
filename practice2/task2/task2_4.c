#include <stdio.h>
void func(void) {
    int arr1[1000];
    int arr2[1000] = {1};
    (void)arr1; (void)arr2;
}
int main(void) {
    func();
    printf("Hello world!\n");
    return 0;
}

