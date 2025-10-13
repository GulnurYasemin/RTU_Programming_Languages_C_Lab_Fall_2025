// week5_task2_struct_save_load.c
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

// Function prototypes
void save_student(Student s, const char *filename);
Student load_student(const char *filename);

int main(void) {
    Student s1;
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    const char *filename = "student.txt";

    // Save student data to file
    printf("Saving student to file...\n");
    save_student(s1, filename);

    // Load data back into a new struct
    printf("Loading student from file...\n");
    Student loaded = load_student(filename);

    // Print loaded data to confirm correctness
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    return 0;
}

// Save student data to text file
void save_student(Student s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    // Write data in simple text format: name age gpa
    fprintf(fp, "%s %d %.2f\n", s.name, s.age, s.gpa);

    if (fclose(fp) != 0) {
        perror("Error closing file after writing");
        exit(EXIT_FAILURE);
    }
}

// Load student data from text file
Student load_student(const char *filename) {
    Student s;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    // Read values in same format as saved
    if (fscanf(fp, "%49s %d %f", s.name, &s.age, &s.gpa) != 3) {
        fprintf(stderr, "Error: invalid file format or missing data.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    if (fclose(fp) != 0) {
        perror("Error closing file after reading");
        exit(EXIT_FAILURE);
    }

    return s;
}
