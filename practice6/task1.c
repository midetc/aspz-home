#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *buf = malloc(10);
    if (!buf) return 1;
    strcpy(buf, "0123456789ABC");
    printf("buf: %s\n", buf);
    free(buf);
    return 0;
}
