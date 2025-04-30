#include <stdio.h>

void func() {
    printf("Now inside func()\n");
}

int main(void) {
    func();
    printf("Returned to main()\n");
    return 0;
}

