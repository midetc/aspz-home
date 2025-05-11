#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define USER_FILE   "userfile.txt"
#define COPY_PATH   "/home/snake/copied.txt"

int main(void) {
    uid_t ruid = getuid();
    uid_t euid = geteuid();

    seteuid(ruid);
    int fd = open(USER_FILE, O_CREAT|O_TRUNC|O_WRONLY, 0644);
    dprintf(fd, "Hello from user %d\n", ruid);
    close(fd);

    seteuid(euid);
    int in = open(USER_FILE, O_RDONLY);
    int out = open(COPY_PATH, O_CREAT|O_TRUNC|O_WRONLY, 0644);
    char buf[4096];
    ssize_t n;
    while ((n = read(in, buf, sizeof(buf))) > 0) {
        write(out, buf, n);
    }
    close(in);
    close(out);

    seteuid(ruid);
    int cw = open(COPY_PATH, O_WRONLY|O_APPEND);
    if (cw < 0) {
        printf("open for write failed: %s\n", strerror(errno));
    } else {
        write(cw, "Trying to append\n", 17);
        close(cw);
        printf("append succeeded\n");
    }

    if (unlink(COPY_PATH) == -1) {
        printf("unlink failed: %s\n", strerror(errno));
    } else {
        printf("unlink succeeded\n");
    }

    return 0;
}
