/*
 * week4_1_dynamic_array.c
 * Name: Serhii Beilakh
 * Student ID: 260ADB195
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int *arr = NULL;

    // Prompt for array size and validate input
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    // Allocate dynamic memory for n integers
    arr = malloc((size_t)n * sizeof(int));

    // Check if memory allocation succeeded
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Prompt user for input values
    printf("Enter %d integers: ", n);

    long long sum = 0; // Use long long to prevent potential integer overflow

    // Read n integers into the dynamic array
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            free(arr); // Clean up memory before exiting
            return 1;
        }
        sum += arr[i];
    }

    // Compute average in double precision floating point
    double average = (double)sum / n;

    // Print results matching exact requirements
    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", average);

    // Free dynamically allocated memory
    free(arr);

    return 0;
}