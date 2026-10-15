/*
 * week4_3_struct_database.c
 * Name: Serhii Beilakh
 * Student ID: 260ADB195
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Use malloc to allocate space for n Student records,
 *   read each record from the user, print them as a table,
 *   and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define struct Student with required fields
struct Student {
  char name[50];
  int id;
  float grade;
};

int main(void) {
  int n;
  struct Student* students = NULL;

  // Prompt for number of students and validate input
  printf("Enter number of students: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid number.\n");
    return 1;
  }

  // Dynamically allocate memory for n Student records
  students = malloc((size_t)n * sizeof(struct Student));

  // Check if memory allocation succeeded
  if (students == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  // Read student records
  for (int i = 0; i < n; i++) {
    printf("Enter data for student %d: ", i + 1);

    // Read name (%49s prevents buffer overflow), id, and grade
    if (scanf("%49s %d %f", students[i].name, &students[i].id,
              &students[i].grade) != 3) {
      printf("Invalid input.\n");
      free(students);  // Clean up allocated memory before exit
      return 1;
    }
  }

  // Print an empty line before table output
  printf("\n");

  // Print table header using exact field widths
  printf("%-6s %-11s %s\n", "ID", "Name", "Grade");

  // Print each student record
  for (int i = 0; i < n; i++) {
    printf("%-6d %-11s %.1f\n", students[i].id, students[i].name,
           students[i].grade);
  }

  // Free allocated memory
  free(students);

  return 0;
}