#include <stdio.h>

int main(void) {
  FILE *file;
  file = fopen("test.txt", "r");
  char ch[100];
  fscanf(file, "%s", ch);
  fscanf(file, "%s", ch);
  //fprintf(file, "test\n");
  fclose(file);
  printf("%s\n", ch);
 return 0; 
}
