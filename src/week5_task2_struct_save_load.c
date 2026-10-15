// week5_task2_struct_save_load.c
// Name: Serhii  Surname: Beilakh  Student ID: 260ADB195
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task2_struct_save_load

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
  char name[MAX_NAME_LEN];
  int age;
  float gpa;
} Student;

// Function prototypes
int save_student(const Student* s,
                 const char* filename);  // 0 on success, -1 on error
int load_student(const char* filename,
                 Student* out);  // 0 on success, -1 on error

int main(void) {
  Student s1 = {0};
  strcpy(s1.name, "Alice");
  s1.age = 21;
  s1.gpa = 3.75f;

  Student loaded = {0};
  const char* filename = "student.txt";

  printf("Saving student to file...\n");
  if (save_student(&s1, filename) != 0) {
    printf("Error: Failed to save student.\n");
    return EXIT_FAILURE;
  }

  printf("Loading student from file...\n");
  if (load_student(filename, &loaded) != 0) {
    printf("Error: Failed to load student.\n");
    return EXIT_FAILURE;
  }

  // Print loaded record in exact required format
  printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age,
         loaded.gpa);

  return EXIT_SUCCESS;
}

// Saves a Student record to a file in "name age gpa" format
int save_student(const Student* s, const char* filename) {
  if (s == NULL || filename == NULL) {
    return -1;
  }

  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    return -1;
  }

  fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);

  fclose(fp);
  return 0;
}

// Loads a Student record from a file and populates the out struct
int load_student(const char* filename, Student* out) {
  if (filename == NULL || out == NULL) {
    return -1;
  }

  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    return -1;
  }

  // Read name, age, gpa and verify all 3 items were parsed correctly
  if (fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa) != 3) {
    fclose(fp);
    return -1;
  }

  fclose(fp);
  return 0;
}