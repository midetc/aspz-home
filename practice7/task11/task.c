#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;
    FILE *in  = fopen(argv[1], "rb");
    FILE *out = fopen(argv[2], "wb");
    if (!in || !out) return 1;
    uint8_t prev = 0, cur;
    int found = 0;
    while (fread(&cur,1,1,in)) {
        if (!found) {
            if (prev==0xFF && cur==0xD8) {
                found = 1;
                fputc(0xFF, out);
                fputc(0xD8, out);
            }
        } else {
            fputc(cur, out);
            if (prev==0xFF && cur==0xD9) break;
        }
        prev = cur;
    }
    fclose(in);
    fclose(out);
    if (!found) {
        remove(argv[2]);
        printf("No JPEG found\n");
        return 1;
    }
    printf("Recovered to %s\n", argv[2]);
    return 0;
}
