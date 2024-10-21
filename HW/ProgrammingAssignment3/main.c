/* COP 3502C Assignment 3 (chatgpt version)
   This programm is written by: Yousef Alaa Awad */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAXN 16  // Maximum number of garages (n <= 8, so 2*n <= 16)

double distance(int x1, int y1, int x2, int y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Solve using DP with bitmasking and store the pairing in 'pairings'
double solve(int mask, int **garages, double **distances, double *dp, int n, int *pairings) {
  if (mask == (1 << (2 * n)) - 1) {
    return 0;  // All garages paired
  }

  if (dp[mask] > -0.5) {
    return dp[mask];  // Return cached result
  }

  double best = DBL_MAX;
  int bestPairA = -1, bestPairB = -1;

  // Find the first unpaired garage
  int firstUnpaired = -1;
  for (int i = 0; i < 2 * n; i++) {
    if (!(mask & (1 << i))) {
      firstUnpaired = i;
      break;
    }
  }

  // Try pairing the first unpaired garage with every other unpaired garage
  for (int j = firstUnpaired + 1; j < 2 * n; j++) {
    if (!(mask & (1 << j))) {
      // Form a pair (firstUnpaired, j), and compute the new mask
      int newMask = mask | (1 << firstUnpaired) | (1 << j);

      // Calculate total distance for this pair + recursively solve for the rest
      double currentDistance = distances[firstUnpaired][j] + solve(newMask, garages, distances, dp, n, pairings);

      // Keep track of the minimum distance found and store the best pair
      if (currentDistance < best) {
        best = currentDistance;
        bestPairA = firstUnpaired;
        bestPairB = j;
      }
    }
  }

  // Store the best pair in the pairings array
  pairings[mask] = (bestPairA << 8) | bestPairB;

  // Cache and return the best distance
  dp[mask] = best;
  return best;
}

// Function to reconstruct and print the pairs based on the 'pairings' array
void printSolution(int mask, int *pairings, int n, char **garageNames, double **distances, int **garages) {
  if (mask == (1 << (2 * n)) - 1) {
    return;  // All garages paired
  }

  int pair = pairings[mask];
  int g1 = (pair >> 8) & 0xFF;
  int g2 = pair & 0xFF;

  // Print the pair and the distance between them
  printf("(%s, %s, %.3lf)\n", garageNames[g1], garageNames[g2], distances[g1][g2]);

  // Form the new mask by marking g1 and g2 as paired and continue
  int newMask = mask | (1 << g1) | (1 << g2);
  printSolution(newMask, pairings, n, garageNames, distances, garages);
}

int main() {
  int n;
  scanf("%d", &n);

  int **garageLocations = calloc(2 * n, sizeof(int *));
  char **garageNames = calloc(2 * n, sizeof(char *));

  for (int i = 0; i < 2 * n; i++) {
    garageLocations[i] = calloc(2, sizeof(int));
    garageNames[i] = calloc(20, sizeof(char));
    scanf("%d %d %s", &garageLocations[i][0], &garageLocations[i][1], garageNames[i]);
  }

  // Precompute all pairwise distances
  double **distances = calloc(2 * n, sizeof(double *));
  for (int i = 0; i < 2 * n; i++) {
    distances[i] = calloc(2 * n, sizeof(double));
    for (int j = 0; j < 2 * n; j++) {
      distances[i][j] = distance(garageLocations[i][0], garageLocations[i][1], garageLocations[j][0], garageLocations[j][1]);
    }
  }

  // Initialize DP array with -1 to indicate unsolved states
  double *dp = calloc(1 << (2 * n), sizeof(double));
  for (int i = 0; i < (1 << (2 * n)); i++) {
    dp[i] = -1.0;
  }

  // Array to store the best pairings
  int *pairings = calloc(1 << (2 * n), sizeof(int));

  // Solve for the minimum distance starting with an empty mask
  double minDistance = solve(0, garageLocations, distances, dp, n, pairings);

  // Print the shortest distance
  printf("%.3lf\n", minDistance);

  // Print the optimal pairings
  printSolution(0, pairings, n, garageNames, distances, garageLocations);

  // Freeing allocated memory
  for (int i = 0; i < 2 * n; i++) {
    free(garageLocations[i]);
    free(garageNames[i]);
    free(distances[i]);
  }
  free(garageLocations);
  free(garageNames);
  free(distances);
  free(dp);
  free(pairings);

  return 0;
}

