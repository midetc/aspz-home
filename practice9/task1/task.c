#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    uid_t me = getuid();
    const int UID_MIN = 1000;
    FILE *fp = popen("getent passwd", "r");
    if (!fp) exit(EXIT_FAILURE);

    char *line = NULL;
    size_t len = 0;
    int found = 0;

    while (getline(&line, &len, fp) > 0) {
        char *copy = strdup(line);
        char *user = strtok(copy, ":");
        strtok(NULL, ":");
        char *uid_str = strtok(NULL, ":");
        int uid = atoi(uid_str);

        if (uid > UID_MIN && uid != me) {
            printf("Other user: %s (UID=%d)\n", user, uid);
            found = 1;
        }
        free(copy);
    }

    free(line);
    pclose(fp);

    if (!found) {
        printf("No other normal users found\n");
    }

    return 0;
}
