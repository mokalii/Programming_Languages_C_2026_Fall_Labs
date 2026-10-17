/*
 * week5_task1_file_io.c
 * Name:ali berk  Surname: cetin Student ID: 251ADB185
 */
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_FILENAME "data.txt"
#define LINE_LEN 256
int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    const char *filename = DEFAULT_FILENAME;
    char line[LINE_LEN];
    int line_count = 0;

    // use another filename if given
    if (argc > 1) {
        filename = argv[1];
    }

    printf("Writing lines to %s...\n", filename);

    // open file and write text
    fp = fopen(filename,"w");

    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");
    fclose(fp);
    //open file and read text
    fp = fopen(filename, "r");

    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    printf("Reading contents:\n");

    while (fgets(line, LINE_LEN, fp) != NULL) {
        printf("%s", line);
        line_count++;
    }
    fclose(fp);
    printf("Lines read: %d\n", line_count);
    return EXIT_SUCCESS;
}