#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

int main(void) {
    uid_t ruid = getuid();
    uid_t euid = geteuid();
    seteuid(ruid);

    char tmpl[] = "/tmp/tmpfileXXXXXX";
    int fd = mkstemp(tmpl);
    write(fd, "test\n", 5);
    close(fd);

    seteuid(euid);
    chown(tmpl, ruid, ruid);
    chmod(tmpl, S_IRUSR | S_IWUSR);

    seteuid(ruid);

    int r = open(tmpl, O_RDONLY);
    if (r < 0)
        printf("read: %s\n", strerror(errno));
    else {
        printf("read: OK\n");
        close(r);
    }

    int w = open(tmpl, O_WRONLY | O_APPEND);
    if (w < 0)
        printf("write: %s\n", strerror(errno));
    else {
        printf("write: OK\n");
        close(w);
    }

    unlink(tmpl);
    return 0;
}
