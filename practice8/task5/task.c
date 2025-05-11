#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    int fd = open("data.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); exit(1); }
    const char *data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (write(fd, data, strlen(data)) != (ssize_t)strlen(data)) { perror("write"); exit(1); }

    char buf[11] = {0};
    off_t positions[] = {0, 5, 10, 20};
    for (int i = 0; i < 4; i++) {
        pread(fd, buf, 10, positions[i]);
        printf("pread at %ld: %s\n", (long)positions[i], buf);
        memset(buf, 0, sizeof(buf));
    }

    off_t before = lseek(fd, 3, SEEK_SET);
    pread(fd, buf, 4, 15);
    off_t after = lseek(fd, 0, SEEK_CUR);
    printf("file offset before pread: %ld\n", (long)before);
    printf("file offset after pread:  %ld\n", (long)after);
    if (read(fd, buf, 4) != 4) { perror("read"); exit(1); }
    printf("read after pread:         %.4s\n", buf);

    close(fd);
    return 0;
}
