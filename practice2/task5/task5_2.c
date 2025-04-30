#include <stdio.h>

void func_return() {
    asm("addq $8, %rsp");
}

void func() {
    printf(">>> Entered func()\n");
    func_return();
}

int main(void) {
    func();
    printf("<<< Returned to main()\n");
    return 0;
}

