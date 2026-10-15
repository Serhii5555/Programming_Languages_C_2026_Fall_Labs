// week5_task3_student_management_system.c
// Name: Serhii  Surname: Beilakh  Student ID: 260ADB195
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
  char name[NAME_LEN];
  int id;
  float gpa;
} Student;

// Function prototypes
int load_students(Student arr[], int max);  // returns number of records loaded
int save_students(const Student arr[], int count);  // 0 on success, -1 on error
void add_student(Student arr[], int* count);
void list_students(const Student arr[], int count);
int read_line(const char* prompt, char* buf, size_t size);

int main(void) {
  Student students[MAX_STUDENTS];
  int count = 0;
  char input[LINE_LEN];
  int running = 1;

  // Load existing data from file
  count = load_students(students, MAX_STUDENTS);
  printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

  while (running) {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");

    int choice;
    if (read_line("Select an option: ", input, sizeof input) != 0) {
      choice = 3;  // end of input: save and exit
    } else {
      char* end;
      long value = strtol(input, &end, 10);
      choice = (end != input && *end == '\0') ? (int)value : 0;
    }

    switch (choice) {
      case 1:
        list_students(students, count);
        break;
      case 2:
        add_student(students, &count);
        break;
      case 3:
        if (save_students(students, count) != 0) {
          printf("Error: Failed to save student data.\n");
        } else {
          printf("Data saved. Goodbye!\n");
        }
        running = 0;
        break;
      default:
        printf("Invalid option. Try again.\n");
    }
  }

  return EXIT_SUCCESS;
}

// Provided helper – prints a prompt and reads one line from stdin into buf.
int read_line(const char* prompt, char* buf, size_t size) {
  printf("%s", prompt);
  fflush(stdout);
  if (fgets(buf, (int)size, stdin) == NULL) {
    return -1;
  }
  size_t len = strcspn(buf, "\r\n");
  if (buf[len] == '\0' && len == size - 1) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
  }
  buf[len] = '\0';
  return 0;
}

// Reads records from DATA_FILE in comma-separated format: name,id,gpa
int load_students(Student arr[], int max) {
  FILE* fp = fopen(DATA_FILE, "r");
  if (fp == NULL) {
    return 0;  // File does not exist yet (first run)
  }

  char line[LINE_LEN];
  int count = 0;

  while (count < max && fgets(line, sizeof(line), fp) != NULL) {
    // Skip blank lines
    if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') {
      continue;
    }

    Student temp;
    // Parse CSV format: name, id, gpa
    if (sscanf(line, "%49[^,],%d,%f", temp.name, &temp.id, &temp.gpa) == 3) {
      arr[count] = temp;
      count++;
    }
  }

  fclose(fp);
  return count;
}

// Saves array of students to DATA_FILE in comma-separated format
int save_students(const Student arr[], int count) {
  FILE* fp = fopen(DATA_FILE, "w");
  if (fp == NULL) {
    return -1;
  }

  for (int i = 0; i < count; i++) {
    fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
  }

  fclose(fp);
  return 0;
}

// Prompts user for student details and validates input
void add_student(Student arr[], int* count) {
  if (*count >= MAX_STUDENTS) {
    printf("Cannot add more students (limit reached).\n");
    return;
  }

  char name[LINE_LEN];
  char id_str[LINE_LEN];
  char gpa_str[LINE_LEN];

  if (read_line("Enter name: ", name, sizeof(name)) != 0 ||
      read_line("Enter ID: ", id_str, sizeof(id_str)) != 0 ||
      read_line("Enter GPA: ", gpa_str, sizeof(gpa_str)) != 0) {
    return;
  }

  // Validate name: non-empty, no commas
  if (strlen(name) == 0 || strchr(name, ',') != NULL) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  // Validate ID: valid integer
  char* end_id;
  long id_val = strtol(id_str, &end_id, 10);
  if (end_id == id_str || *end_id != '\0') {
    printf("Invalid input. Student not added.\n");
    return;
  }

  // Validate GPA: valid float between 0.0 and 4.0
  char* end_gpa;
  float gpa_val = strtof(gpa_str, &end_gpa);
  if (end_gpa == gpa_str || *end_gpa != '\0' || gpa_val < 0.0f ||
      gpa_val > 4.0f) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  // Store record
  strncpy(arr[*count].name, name, NAME_LEN - 1);
  arr[*count].name[NAME_LEN - 1] = '\0';
  arr[*count].id = (int)id_val;
  arr[*count].gpa = gpa_val;

  (*count)++;
  printf("Student added successfully!\n");
}

// Displays student records in a formatted table
void list_students(const Student arr[], int count) {
  if (count == 0) {
    printf("No students found.\n");
    return;
  }

  printf("%-6s %-20s %s\n", "ID", "Name", "GPA");
  for (int i = 0; i < count; i++) {
    printf("%-6d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
  }
}