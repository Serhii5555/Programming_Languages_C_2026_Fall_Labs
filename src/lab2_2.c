#include <stdio.h>

/*
    Task:
    Write a function `long long factorial(int n)` that computes n!
    using a loop (not recursion).

    In main():
      - Ask user for an integer n
      - If n is negative, print an error and exit
      - Otherwise, call factorial and print the result
*/

long long factorial(int n) {
  long long result = 1;

  for (int i = 1; i <= n; i++) {
    result *= i;
  }

  return result;
}

int main(void) {
  int n;

  printf("Enter a non-negative integer n: ");
  scanf("%d", &n);

  if (n < 0) {
    printf("Error: n must be a non-negative integer.\n");
  } else {
    long long factorial_result = factorial(n);
    printf("The factorial of %d is: %lld\n", n, factorial_result);
  }
  return 0;
}