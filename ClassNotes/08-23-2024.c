#include <stdio.h>

// a function to swap variables using pointers!!!
void swapvar(int *x, int *y) {
  // declaring an internal temporary variable.
  int temp;
  // assigning the temp variable to x's value.
  temp = *x;
  // assigning x to be y's value.
  *x = *y;
  // assigning y to temp's value.
  *y = temp;
}

int main() {
  // funny c review still.
  int x = 5, y = 7, *p1, *p2;
  p1 = &x;
  p2 = &y;
  *p1 = 50; // x is now 50.
  p1 = p2;  // p1 now points to y.
  *p1 = 8;  // y is now 8.
  p2 = &x;
  *p2 = *p1; // y is now the same value as x, but done indirectly (aka not using
             // x and y proper)
  printf("y is finally %d\nx is finally %d\n", y, x);
  // remember that pointers are just used so that you can store the address, and
  // pass in functions and structures efficiently.

  printf("\n");

  // now for swapping variables :p
  int var1 = 1, var2 = 2;
  // reassigning previous pointers to make the code more efficient.
  p1 = &var1;
  p2 = &var2;
  // calling the function to swap the 2 variables (no matter the type).
  swapvar(p1, p2);
  // checking if the variables actually swapped!!!
  printf("var1 was 1, now it is %d.\nvar2 was 2, now it is %d\n", var1, var2);

  return 0;
}
