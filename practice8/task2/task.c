#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int fd = open("data.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); exit(1); }
    unsigned char data[] = {4,5,2,2,3,3,7,9,1,5};
    if (write(fd, data, sizeof(data)) != sizeof(data)) { perror("write"); exit(1); }
    lseek(fd, 3, SEEK_SET);
    unsigned char buffer[4];
    if (read(fd, buffer, sizeof(buffer)) < 0) { perror("read"); exit(1); }
    printf("Buffer: %u %u %u %u\n",
           buffer[0], buffer[1], buffer[2], buffer[3]);
    close(fd);
    return 0;
}
