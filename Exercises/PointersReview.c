#include <stdio.h>

void NULLT(int **p) {
  *p = NULL;
}

int main() {
  float a = 13.5;
  float *b, *c;
  b = &a;
  c = b;
  printf("b is %u and c is %u while a is %u\n", b, c, &a);

  int f[5] = {5, 2, 15, 20, 25};
  int i, j, k = 1, m;
  i = ++f[1]; // i is 2, and a[1] is also 2.
  j = f[1]++; // j is 2. while a[1] is now 3.
  m = f[i++]; // i is 3, and now m is 15.
  printf("%d, %d, %d", i, j, m);

  int n[3][3] = {2, 4, 3, 6, 8, 5, 3, 5, 1};
  printf("\n%d %d %d\n", *n, n[3][3], n[2][2]);

  for (i = 0; i <= 2; i++)
    for (j = 0; j <= 2; j++)
      printf("%d\n", *(*(n + i) + j));

  int *h;
  NULLT(&h);
  printf("%p", h);

  return 0;
}
