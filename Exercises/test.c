#include <stdio.h>
int octal(int decimal) {
  if (decimal < 8) {
    printf("%d", decimal % 8);
    return decimal % 8;
  }
  octal(decimal / 8);
  printf("%d", decimal % 8);
  return 0;
}

int main() { octal(10); }
