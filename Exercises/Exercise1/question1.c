#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float **AllocateArrayOfArrays(int P, int *Lengths) {
  float **array2d = calloc(P, sizeof(float *));
  srand(time(NULL));
  for (int i = 0; i < P; i++) {
    array2d[i] = calloc(Lengths[i], sizeof(float));
    for (int j = 0; j < Lengths[i]; j++) {
      array2d[i][j] = (float)((rand() % 100) + 1);
    }
  }
  return array2d;
}

int main() {

  int length[5] = {2, 4, 6, 3, 9};

  float **array =AllocateArrayOfArrays(5, length);

  for (int i = 0; i < 5; i++) {
    free(array[i]);
  }
  free(array);

  return 0;
}
