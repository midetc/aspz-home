#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int flags = fcntl(pipefd[1], F_GETFL);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }
    if (fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL");
        exit(EXIT_FAILURE);
    }

    size_t nbytes = 100000;
    char *buffer = malloc(nbytes);
    if (!buffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    memset(buffer, 'A', nbytes);

    ssize_t count = write(pipefd[1], buffer, nbytes);
    if (count == -1) {
        perror("write");
    } else {
        printf("Attempted to write: %zu bytes\n", nbytes);
        printf("Actually written:   %zd bytes\n", count);
    }

    free(buffer);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
