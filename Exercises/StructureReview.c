#include <stdio.h>
#include <string.h>
/*
typedef struct X {
  int num;
  int *y;
} X;

int main() {
  X x;
  X *p;
  p = &x;
  x.num = 10;
  x.y = &x.num;

  printf("%d %d %u %u %u %d %d", p->num, (*p).num, &x.num, x.y, p->y, *(x.y),
         *(p->y));
  return 0;
}*/

/*struct test {
  int x;
  int *p;
};

int main() {
   struct test t;
   int y;
   t.x = 50;
   t->p = &y;
   return 0;
}*/

/*struct Point { int x; int y; };
void add(struct Point p[], int a, int b) {
  for (int i=0; i<2; i++) {
    p[i].x +=a;
    p[i].y +=b;
  }
}*/

int main() {
  char c[6] = "cat";
  printf("%lu", strlen(c));
}
