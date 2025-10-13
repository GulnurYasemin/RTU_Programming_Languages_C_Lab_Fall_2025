// week5_task3_student_management_system.c
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define DATA_FILE "students.txt"

typedef struct {
  char name[NAME_LEN];
  int id;
  float gpa;
} Student;

// Function prototypes
int load_students(Student arr[]);
void save_students(Student arr[], int count);
void add_student(Student arr[], int *count);
void list_students(Student arr[], int count);

// helper
static void trim_newline(char *s) {
  if (!s) return;
  size_t n = strlen(s);
  if (n && (s[n - 1] == '\n' || s[n - 1] == '\r')) s[n - 1] = '\0';
}

int main(void) {
  Student students[MAX_STUDENTS];
  int count = 0;
  int choice;

  // Load existing data from file using load_students()
  count = load_students(students);

  do {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");
    printf("Select an option: ");
    if (scanf("%d", &choice) != 1) {
      // clear bad input
      int ch;
      while ((ch = getchar()) != '\n' && ch != EOF) {
      }
      printf("Invalid input. Try again.\n");
      continue;
    }
    getchar();  // clear trailing newline

    switch (choice) {
      case 1:
        list_students(students, count);
        break;
      case 2:
        add_student(students, &count);
        break;
      case 3:
        save_students(students, count);
        printf("Data saved. Goodbye!\n");
        break;
      default:
        printf("Invalid option. Try again.\n");
    }
  } while (choice != 3);

  return 0;
}

// Open DATA_FILE, read records until EOF, return number of records loaded
// Line format: name<TAB>id<TAB>gpa
int load_students(Student arr[]) {
  FILE *fp = fopen(DATA_FILE, "r");
  if (!fp) {
    // Missing file is fine; start empty
    return 0;
  }

  int count = 0;
  char line[256];

  while (fgets(line, (int)sizeof(line), fp) != NULL && count < MAX_STUDENTS) {
    trim_newline(line);
    if (line[0] == '\0') continue;

    Student s = {0};
    if (sscanf(line, " %49[^\t]\t%d\t%f", s.name, &s.id, &s.gpa) == 3) {
      arr[count++] = s;
    }
    // malformed lines are skipped
  }

  if (fclose(fp) != 0) {
    perror("Failed to close students file after reading");
  }

  return count;
}

// Write all students to DATA_FILE
void save_students(Student arr[], int count) {
  FILE *fp = fopen(DATA_FILE, "w");
  if (!fp) {
    perror("Failed to open students file for writing");
    return;
  }

  for (int i = 0; i < count; ++i) {
    if (fprintf(fp, "%s\t%d\t%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
      perror("Failed to write a student record");
    }
  }

  if (fclose(fp) != 0) {
    perror("Failed to close students file after writing");
  }
}

// Read input from user and append to array
void add_student(Student arr[], int *count) {
  if (*count >= MAX_STUDENTS) {
    printf("Array full. Cannot add more students.\n");
    return;
  }

  Student s = {0};
  char buf[256];

  printf("Enter name: ");
  if (!fgets(buf, (int)sizeof(buf), stdin)) return;
  trim_newline(buf);
  if (buf[0] == '\0') {
    printf("Name cannot be empty.\n");
    return;
  }
  strncpy(s.name, buf, NAME_LEN - 1);

  printf("Enter ID: ");
  if (!fgets(buf, (int)sizeof(buf), stdin)) return;
  s.id = (int)strtol(buf, NULL, 10);

  printf("Enter GPA: ");
  if (!fgets(buf, (int)sizeof(buf), stdin)) return;
  s.gpa = strtof(buf, NULL);

  arr[(*count)++] = s;
  printf("Student added successfully!\n");
}

// Print all students in readable format
void list_students(Student arr[], int count) {
  if (count == 0) {
    printf("No students found.\n");
    return;
  }

  printf("\n%-4s | %-30s | %-8s | %-5s\n", "#", "Name", "ID", "GPA");
  printf("-------------------------------------------------------\n");
  for (int i = 0; i < count; ++i) {
    printf("%-4d | %-30s | %-8d | %-5.2f\n", i + 1, arr[i].name, arr[i].id,
           arr[i].gpa);
  }
}
