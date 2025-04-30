#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    pid_t pid = getpid();

    printf("Аналіз памʼяті процесу з PID: %d\n\n", pid);

    char command[64];
    snprintf(command, sizeof(command), "procstat -v %d", pid);

    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Помилка виконання команди procstat\n");
        return 1;
    }

    return 0;
}
