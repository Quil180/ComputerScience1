/* COP 3502C Assignment 3
   This programm is written by: Yousef Alaa Awad */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double distance(int x1, int y1, int x2, int y2) {
  // function to calculate the distance between 2 garages given the coordinates.
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void print(int **locations, char **names, int n) {
  // prints out the given garages and their names, only used for testing
  // purposes.
  for (int i = 0; i < n; i++) {
    printf("%s -> (%d, %d) ", names[i], locations[i][0], locations[i][1]);
  }
  printf("\n");
}

void printperms(int **garages, char **names, int *usedgarages, int *perm,
                int final[][2], int k, int n, double *min) {
  // goes through every permutation and then finds the distance.
  if (k == n) {
    double calcdistance = 0;
    for (int i = 0; i < n; i += 2) {
      calcdistance +=
          distance(garages[perm[i]][0], garages[perm[i]][1],
                   garages[perm[i + 1]][0], garages[perm[i + 1]][1]);
    }

    if (calcdistance < *min) {
      // if the distance is smaller than the distance minimum found before it,
      // replace that distance.
      *min = calcdistance;
      for (int i = 0; i < n; i += 2) {
        final[i / 2][0] = perm[i];
        final[i / 2][1] = perm[i + 1];
      }
    }

    return;
  }

  for (int i = 0; i < n; i++) {
    if (!usedgarages[i]) {
      // if the garage was not already used, then just say it is and call the
      // function recursively.
      usedgarages[i] = 1;
      perm[k] = i;
      printperms(garages, names, usedgarages, perm, final, k + 1, n, min);
      // unset the garage after its been used.
      usedgarages[i] = 0;
    }
  }
}

int main() {
  int n = 0;

  // getting the amount of expressways/garages
  scanf("%d", &n);

  int **garageLocations = calloc(2 * n, sizeof(int *));
  // allocating the space for all the garage names.
  char **garageNames = calloc(2 * n, sizeof(char *));

  for (int i = 0; i < 2 * n; i++) {
    // allocating space for every garage
    garageLocations[i] = calloc(2, sizeof(int));
    // 20 being the max length of a garage name
    garageNames[i] = calloc(20, sizeof(char));

    // getting the data from the input and putting it into the allocated space
    scanf("%d %d %s", &garageLocations[i][0], &garageLocations[i][1],
          garageNames[i]);
  }

  // more variable declarations
  double min = 9999999999;
  int *used = calloc(2 * n, sizeof(int));
  int *perm = calloc(2 * n, sizeof(int));
  int final[n * 2][2];

  // recursion starts here
  printperms(garageLocations, garageNames, used, perm, final, 0, 2 * n, &min);

  // printing the shortest distance
  printf("%.3lf\n", min);
  // printing the permutation that generated that distance.
  for (int i = 0; i < n; i++) {
    int g1 = final[i][0], g2 = final[i][1];
    printf("(%s, %s, %.3lf)\n", garageNames[g1], garageNames[g2],
           distance(garageLocations[g1][0], garageLocations[g1][1],
                    garageLocations[g2][0], garageLocations[g2][1]));
  }

  // freeing all the dynamically allocated memory
  for (int i = 2 * n - 1; i > -1; i--) {
    free(garageLocations[i]);
    free(garageNames[i]);
  }
  free(used);
  free(perm);
  free(garageNames);
  free(garageLocations);

  // end of program
  return 0;
}
