#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define CHUNK       1024
#define SIZE_LIMIT (1024 * 1024)  /* 1 MB */

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Program need two arguments\n");
        return EXIT_FAILURE;
    }

    const char *inPath  = argv[1];
    const char *outPath = argv[2];

    if (strcmp(inPath, outPath) == 0) {
        fprintf(stderr, "Error: source and destination must be different\n");
        return EXIT_FAILURE;
    }
    struct stat st1, st2;
    if (stat(inPath, &st1) == 0 && stat(outPath, &st2) == 0) {
        if (st1.st_dev == st2.st_dev && st1.st_ino == st2.st_ino) {
            fprintf(stderr, "Error: source and destination refer to the same file\n");
            return EXIT_FAILURE;
        }
    }

    FILE *fin  = fopen(inPath,  "rb");
    if (!fin) {
        fprintf(stderr, "Cannot open file %s for reading\n", inPath);
        return EXIT_FAILURE;
    }

    FILE *fout = fopen(outPath, "wb");
    if (!fout) {
        fclose(fin);
        fprintf(stderr, "Cannot open file %s for writing\n", outPath);
        return EXIT_FAILURE;
    }

    unsigned char buf[CHUNK];
    size_t n, written = 0;

    while ((n = fread(buf, 1, CHUNK, fin)) > 0) {
        if (written + n > SIZE_LIMIT) {
            fprintf(stderr,
                "Error: File size limit exceeded while writing to %s\n",
                outPath
            );
            fclose(fin);
            fclose(fout);
            return EXIT_FAILURE;
        }
        if (fwrite(buf, 1, n, fout) != n) {
            fprintf(stderr, "Error writing to file %s\n", outPath);
            fclose(fin);
            fclose(fout);
            return EXIT_FAILURE;
        }
        written += n;
    }

    fclose(fin);
    fclose(fout);

    printf("File successfully copied from %s to %s\n", inPath, outPath);
    return EXIT_SUCCESS;
}
