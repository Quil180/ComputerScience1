#include <stdlib.h>
int main () {
  int *array1 = (int *)malloc(20);
  int *array2 = (int *)malloc(20);

  array2 = array1;

  free(array1);
  

  return 0;
}
