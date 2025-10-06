/*
 * week4_3_struct_database.c
 * Author: [Gulnur Yasemin UYGUN]
 * Student ID: [231ADB101]
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Demonstrates using malloc to allocate memory for multiple Student records,
 *   reading input, displaying a formatted table, and freeing memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Define struct Student
struct Student {
    char name[50];
    int id;
    float grade;
};

// Helper: clears leftover input (after scanf)
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    int n;
    struct Student *students = NULL;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 1;
    }

    //  Allocate memory for n Student structs using malloc
    students = (struct Student *)malloc(n * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    clear_input_buffer(); // remove newline left by scanf

    //  Read student data in a loop
    for (int i = 0; i < n; i++) {
        printf("\nEnter data for student %d\n", i + 1);

        printf("  Name: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        // remove newline from fgets
        students[i].name[strcspn(students[i].name, "\n")] = '\0';

        printf("  ID: ");
        scanf("%d", &students[i].id);

        printf("  Grade: ");
        scanf("%f", &students[i].grade);

        clear_input_buffer(); // clear buffer for next iteration
    }

    //  Display all student records in formatted output
    printf("\n%-6s %-20s %-6s\n", "ID", "Name", "Grade");
    for (int i = 0; i < n; i++) {
        printf("%-6d %-20s %-6.2f\n",
               students[i].id,
               students[i].name,
               students[i].grade);
    }

    //  Optional: compute average grade
    float total = 0.0f;
    for (int i = 0; i < n; i++)
        total += students[i].grade;

    printf("\nAverage grade: %.2f\n", total / n);

    //  Free allocated memory
    free(students);

    return 0;
}
