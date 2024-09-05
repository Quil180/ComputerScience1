#include <stdio.h>
#include <stdlib.h>

int main() {
  malloc(2); // returns a void pointer where the data type is not
             // specified (and therefore could be anything). It
             // allocates based on bytes listed in the parenthesis.

  

  printf("test\n");
  return 0;
}
