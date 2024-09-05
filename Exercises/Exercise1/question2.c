#include <stdlib.h>
#include <string.h>
typedef struct Employee {
  char *first;
  char *last;
  int ID;
} Employee;

Employee *makeArray(char **firstNames, char **lastNames, int *IDs, int n) {
  int i;
  Employee *array = (Employee *)malloc(n * sizeof(Employee));
  for (i = 0; i < n; i++) {
    array[i].first = (char *)malloc((strlen(firstNames[i]) + 1) * sizeof(char));
    array[i].last = (char *)malloc((strlen(lastNames[i]) + 1) * sizeof(char));
    strcpy(array[i].first, firstNames[i]);
    strcpy(array[i].last, lastNames[i]);
    array[i].ID = IDs[i];
  }
  return array;
}

void freeEmployeesArray(Employee *array, int n) {
  for (int i = 0; i < n; i++) {
    free(array[i].last);
    free(array[i].first);
  }
  free(array);
}

int main () {
  int n = 2;
  char *firstNames[2] = {"Bob", "Bill"};
  char *lastNames[2] = {"Handy", "Sandy"};
  int IDs[2] = {1, 2};
  Employee *test = makeArray(firstNames, lastNames, IDs, n);

  freeEmployeesArray(test, n);
}
