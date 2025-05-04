#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *build_message(const char *text)
{
    char *msg = malloc(strlen(text) + 1);
    if (!msg) exit(EXIT_FAILURE);
    strcpy(msg, text);
    return msg;
}

static void log_and_maybe_free(char *p)
{
    printf("log: %s\n", p);
    free(p);
}

int main(void)
{
    char *msg = build_message("Hello, FreeBSD!");
    printf("before: %s\n", msg);
    log_and_maybe_free(msg);
    printf("after:  %s\n", msg);  
    free(msg);                    
    return 0;
}
