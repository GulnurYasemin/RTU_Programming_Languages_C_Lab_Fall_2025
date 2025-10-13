// week5_task1_file_io.c
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp;
    char filename[100] = "data.txt";
    char line[256];
    int line_count = 0;

    // --- 1. Open file for writing ---
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }

    printf("Writing lines to %s...\n", filename);

    // --- 2. Write lines to the file ---
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");
    fprintf(fp, "Goodbye!\n");

    // --- 3. Close the file after writing ---
    if (fclose(fp) != 0) {
        perror("Error closing file after writing");
        return EXIT_FAILURE;
    }

    // --- 4. Open file for reading ---
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }

    printf("Reading contents:\n");

    // --- 5. Read file line by line ---
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
        line_count++;
    }

    // --- 6. Check for reading errors ---
    if (ferror(fp)) {
        perror("Error reading from file");
        fclose(fp);
        return EXIT_FAILURE;
    }

    // --- 7. Close file ---
    if (fclose(fp) != 0) {
        perror("Error closing file after reading");
        return EXIT_FAILURE;
    }

    printf("\nTotal lines read: %d\n", line_count);

    return EXIT_SUCCESS;
}
