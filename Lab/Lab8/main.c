/* COP 3502C Lab 8
This program is written by: Yousef Alaa Awad */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMARRAYS 6
#define MAXVAL 1000000
#define THRESHOLD 25

void randArray(int A[], int size, int maxval);
void bubbleSort(int A[], int n);
void insertionSort(int arr[], int n);
void swap(int *a, int *b);
void arrayCopy(int from[], int to[], int size);
long timediff(clock_t t1, clock_t t2);
void selectionSort(int a[], int n);
void mergeSort(int a[], int left, int right);
int partition(int arr[], int left, int right);
void quickSort(int arr[], int left, int right);
void merge(int a[], int left, int middle, int right);
void mergeInsertion(int arr[], int left, int right);

int main() {

  // Different sizes to test the sort.
  int sizes[NUMARRAYS] = {10000, 20000, 30000, 40000, 50000, 100000};

  int *originalArray; // to keep the original array unchanged so that we can use
  // it for various algorithms.
  int *sortedArray; // We will mainly pass this one to all the function.
  int i, j;
  int start, end;

  // Loop through trying each size.
  for (i = 0; i < NUMARRAYS; i++) {

    // Allocate the space for the array and fill it.
    originalArray = (int *)malloc(sizeof(int) * sizes[i]);
    sortedArray = (int *)malloc(sizeof(int) * sizes[i]);

    randArray(originalArray, sizes[i], MAXVAL);

    arrayCopy(originalArray, sortedArray, sizes[i]);
    clock_t start, end;
    start = clock();
    bubbleSort(sortedArray, sizes[i]);
    end = clock();
    long elapsed = timediff(start, end);
    printf("\nsorting %d values takes %ld milli seconds for Bubble sort\n",
           sizes[i], elapsed);

    arrayCopy(originalArray, sortedArray, sizes[i]);
    start = clock();
    selectionSort(sortedArray, sizes[i]);
    end = clock();
    elapsed = timediff(start, end);
    printf("\nsorting %d values takes %ld milli seconds for Selection sort\n",
           sizes[i], elapsed);

    arrayCopy(originalArray, sortedArray, sizes[i]);
    start = clock();
    mergeSort(sortedArray, 0, sizes[i] - 1);
    end = clock();
    elapsed = timediff(start, end);
    printf("\nsorting %d values takes %ld milli seconds for Merge sort\n",
           sizes[i], elapsed);

    arrayCopy(originalArray, sortedArray, sizes[i]);
    start = clock();
    quickSort(sortedArray, 0, sizes[i] - 1);
    end = clock();
    elapsed = timediff(start, end);
    printf("\nsorting %d values takes %ld milli seconds for Quick sort\n",
           sizes[i], elapsed);

    arrayCopy(originalArray, sortedArray, sizes[i]);
    start = clock();
    insertionSort(sortedArray, sizes[i]);
    end = clock();
    elapsed = timediff(start, end);
    printf("\nsorting %d values takes %ld milli seconds for Insertion sort\n",
           sizes[i], elapsed);

    arrayCopy(originalArray, sortedArray, sizes[i]);
    start = clock();
    mergeInsertion(sortedArray, 0, sizes[i] - 1);
    end = clock();
    elapsed = timediff(start, end);
    printf("\nsorting %d values takes %ld milli seconds for Merge Insertion sort\n",
           sizes[i], elapsed);

    free(sortedArray);
    free(originalArray);
  }

  system("PAUSE");
  return 0;
}

void arrayCopy(int from[], int to[], int size) {
  int j;
  for (j = 0; j < size; j++)
    to[j] = from[j];
}

void randArray(int A[], int size, int maxval) {

  int i;
  // Fill each array slot in question with a random value in the designated
  // range.
  for (i = 0; i < size; i++)
    A[i] = rand() % maxval + 1;
}

// Sorts the first length elements of vals in ascending order.
void bubbleSort(int A[], int n) {

  int i, j;

  // Loop through each element to insert.
  for (i = 0; i < n - 1; i++) {

    for (j = 0; j <= n - i - 1; j++) {
      if (A[j] > A[j + 1])
        swap(&A[j], &A[j + 1]);
    }
  }
}

// Swaps the integers pointed to by a and b.
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void insertionSort(int arr[], int n) {
  int i, item, j;
  for (i = 1; i < n; i++) {
    item = arr[i];

    /* Move elements of arr[0..i-1], that are
      greater than key, to one position ahead
      of their current position */
    for (j = i - 1; j >= 0; j--) {
      if (arr[j] > item)
        arr[j + 1] = arr[j];
      else
        break;
    }
    arr[j + 1] = item;
  }
}

int partition(int arr[], int left, int right) {
  int torque = arr[right];
  int i = left - 1;
  for (int j = left; j <= right - 1; j++) {
    if (arr[j] <= torque) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[right]);
  return (i + 1);
}

void quickSort(int arr[], int left, int right) {
  if (left < right) {
    int pizza = partition(arr, left, right);
    quickSort(arr, left, pizza - 1);
    quickSort(arr, pizza + 1, right);
  }
}

void merge(int a[], int left, int middle, int right) {
  int i, j, k;

  int n1 = middle - left + 1; // size of the left array
  int n2 = right - middle;    // size of the right array

  // dynamically allocating the space for the left and right array sizes (as
  // they are unknown).
  int *lArr = calloc(n1, sizeof(int));
  int *rArr = calloc(n2, sizeof(int));

  // copying the data into the respective arrays.
  for (i = 0; i < n1; i++) {
    // copying into the left array
    lArr[i] = a[left + i];
  }
  for (j = 0; j < n2; j++) {
    // copying into the right array
    rArr[j] = a[(middle + 1) + j];
  }

  // reusing i and j for the trackers for merging
  i = 0;
  j = 0;
  k = left;

  while (i < n1 && j < n2) {
    // while both trackers are still inside of the array, check which array
    // element is smaller
    if (lArr[i] < rArr[j]) {
      // the left array is smaller
      a[k] = lArr[i];
      i += 1;
      k += 1;
    } else {
      // the right array is smaller
      a[k] = rArr[j];
      j += 1;
      k += 1;
    }
  }
  // What if we have any remaining?
  while (i < n1) {
    // if the left array isn't empty
    a[k] = lArr[i];
    i += 1;
    k += 1;
  }
  while (j < n2) {
    // if the right array isnt empty
    a[k] = rArr[j];
    j += 1;
    k += 1;
  }
  // freeing up the allocated memory
  free(lArr);
  free(rArr);
}
void mergeSort(int a[], int left, int right) {
  if (left < right) {
    // calculate the middle of the given array
    int middle = (left + right) / 2;

    // call the mergeSort function recursively for the left and right side
    mergeSort(a, left, middle);
    mergeSort(a, middle + 1, right);

    // after reaching the array size of one (as it'd never get into this if
    // statement), begin to merge the aray blocks.
    merge(a, left, middle, right);
  }
}

void selectionSort(int a[], int n) {
  for (int i = 0; i < (n - 1); i++) {
    // find the minimum value from i to n - 1.
    int min = a[i];
    int mini = i;
    for (int j = (i + 1); j < (n - 1); j++) {
      if (min > a[j]) { // if we want to sort descending, change to <
        // we found a smaller value
        min = a[j];
        mini = j;
      }
    }

    // now we swap the values
    swap(&a[mini], &a[i]);
  }
}

void mergeInsertion(int arr[], int left, int right) {
  if (right - left + 1 <= THRESHOLD) {
    insertionSort(arr, right - left + 1);
  } else if (left < right) {
    int middle = (right + left) / 2;
    mergeInsertion(arr, left, middle);
    mergeInsertion(arr, middle + 1, right);
    merge(arr, left, middle, right);
  }
}

long timediff(clock_t t1, clock_t t2) {
  long elapsed;
  elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
  return elapsed;
}
