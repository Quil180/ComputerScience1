/* COP 3502C Programming Assignment 4
This program is written by: Yousef Alaa Awad */

#include <stdio.h>
#include <stdlib.h>

int X = 0, Y = 0;

struct garage {
  int x;
  int y;
  int rank;
  int found;
};

struct garage *readData(int *x, int *y, int *numG, int *numP, int *threshold) {
  scanf("%d %d %d %d %d", x, y, numG, numP, threshold);
  struct garage *array = (struct garage *)malloc(sizeof(struct garage) * *numG);

  for (int i = 0; i < *numG; i++) {
    scanf("%d %d", &array[i].x, &array[i].y);
  }

  return array;
}

int compareTo(struct garage *g1, struct garage *g2) {
  // return a -1 if the first garage is closer than the second garage to you.
  // return a 0 if the first garage is in the same spot as the second garage.
  // return a +1 if the first garage is farther than the second garage.

  // some exceptions:
  //  if the garages are the same distance, then return a -1 if the first
  //  garage's x-coord is lower than the second.
  //    return a +1 if first garage's x-coord is higher than the second.
  //  if the x-coords are the same, return -1 if the first garage's y-coord is
  //  lower, and if it's higher than return +1.

  int distance1 = (X - g1->x)*(X - g1->x) + (Y - g1->y)*(Y - g1->y);
  int distance2 = (X - g2->x)*(X - g2->x) + (Y - g2->y)*(Y - g2->y);

  if (distance1 < distance2) {
    // the first garage is closer.
    return -1;
  } else if (distance1 > distance2) {
    // the first garage is farther.
    return 1;
  } else if (g1->x == g2->x && g1->y == g2->y) {
    // its the same garage.
    return 0;
  } else {
    if (g1->x < g2->x) {
      return -1;
    } else if (g1->x > g2->x) {
      return 1;
    } else if (g1->y < g2->y) {
      return -1;
    } else if (g1->y > g2->y) {
      return 1;
    } else {
      return 0;
    }
  }
}

// Insertion Sort Functions are below
void insertionSort(struct garage arr[], int first, int last) {
  for (int i = first; i <= last; i++) {
    int j = i - 1;
    struct garage hand = arr[i];
    while (j >= first && compareTo(&arr[j], &hand) > 0) {
      arr[j + 1] = arr[j];
      arr[j + 1].rank = j + 1;
      j -= 1;
    }
    arr[j + 1] = hand;
    arr[j + 1].rank = j + 1;
  }
}

// Binary Search Functions are below
int binarySearch(struct garage a[], struct garage item, int size) {
  int left = 0, right = size - 1, middle;

  while (left <= right) {
    middle = (left + right) / 2;
    int comp = compareTo(&a[middle], &item);

    if (comp == 0) {
      // the item is the middle number.
      return middle;
    }
    if (comp < 0) {
      // the item is greater than the middle number
      left = middle + 1;
    } else {
      // the item is less than the middle number
      right = middle - 1;
    }
  }

  // the item is not in the list.
  return -1;
}

// Regular Merge Sort Functions are below
void merge(struct garage a[], int left, int middle, int right) {
  int n1 = middle - left + 1; // size of the left array
  int n2 = right - middle;    // size of the right array

  // dynamically allocating the space for the left and right array sizes (as
  // they are unknown).
  struct garage *lArr = calloc(n1, sizeof(struct garage));
  struct garage *rArr = calloc(n2, sizeof(struct garage));

  // copying the data into the respective arrays.
  for (int i = 0; i < n1; i++) {
    // copying into the left array
    lArr[i] = a[left + i];
  }
  for (int j = 0; j < n2; j++) {
    // copying into the right array
    rArr[j] = a[middle + 1 + j];
  }

  // reusing i and j for the trackers for merging
  int i = 0, j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    // while both trackers are still inside of the array, check which array
    // element is smaller
    if (compareTo(&lArr[i], &rArr[j]) <= 0) {
      // the left array is smaller
      a[k] = lArr[i];
      a[k].rank = k;
      i += 1;
      k += 1;
    } else {
      // the right array is smaller
      a[k] = rArr[j];
      a[k].rank = k;
      j += 1;
      k += 1;
    }
  }
  // What if we have any remaining?
  while (i < n1) {
    // if the left array isn't empty
    a[k] = lArr[i];
    a[k].rank = k;
    i += 1;
    k += 1;
  }
  while (j < n2) {
    // if the right array isnt empty
    a[k] = rArr[j];
    a[k].rank = k;
    j += 1;
    k += 1;
  }
  // freeing up the allocated memory
  free(lArr);
  free(rArr);
}

void mergeSort(struct garage a[], int left, int right, int threshold) {
  if (right - left < threshold) {
    insertionSort(a, right, left);
  }
  if (left < right) {
    // calculate the middle of the given array
    int middle = (left + right) / 2;

    // call the mergeSort function recursively for the left and right side
    mergeSort(a, left, middle, threshold);
    mergeSort(a, middle + 1, right, threshold);

    // after reaching the array size of one (as it'd never get into this if
    // statement), begin to merge the aray blocks.
    merge(a, left, middle, right);
  }
}

void wrapSort(struct garage a[], int length, int threshold) {
  mergeSort(a, 0, length - 1, threshold);
}

// only used for testing
void printArray(struct garage sorted[], int sortedL, struct garage search[],
                int searchL) {
  for (int i = 0; i < sortedL; i++) {
    printf("%d %d\n", sorted[i].x, sorted[i].y);
  }
  for (int i = 0; i < searchL; i++) {
    if (search[i].found != -1) {
      printf("%d %d garage found at position %d in the order\n", search[i].x,
             search[i].y, search[i].rank);
    } else {
      printf("%d %d no garage found\n", search[i].x, search[i].y);
    }
  }
}

int main() {
  int numG, numP, threshold;
  struct garage *array = readData(&X, &Y, &numG, &numP, &threshold);

  struct garage *search = (struct garage *)malloc(sizeof(struct garage) * numP);
  for (int i = 0; i < numP; i++) {
    scanf("%d %d", &(search[i].x), &(search[i].y));
    search[i].found = -1;
  }

  wrapSort(array, numG, threshold);

  for (int i = 0; i < numP; i++) {
    search[i].found = binarySearch(array, search[i], numG);
    search[i].rank = search[i].found + 1;
  }

  printArray(array, numG, search, numP);

  free(array);
  free(search);
  return 0;
}
