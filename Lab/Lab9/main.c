/* Cop 3502C Lab 9 Heaps
This program is wrriten by: Yousef Awad*/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

// GOAL: In this lab we will write a code that will check whether an array
// represents a minheap or not.

int isHeap_recursive(int arr[], int i, int n) {
  // if i is outside of the array range, it means this part is a heap because we
  // already confirmed that all nodes are valid
  if (i >= n || n <= 0) {
    return 1;
  }

  // if there is a left child, compare with it
  if ((2 * i + 1) < n) {
    if (arr[2 * i + 1] < arr[i]) {
      return 0;
    }
  }

  // if there is a right, compare with it
  if ((2 * i + 2) < n) {
    if (arr[2 * i + 2] < arr[i]) {
      return 0;
    }
  }

  // recursively go the the left and right child and return the final result
  // based on && operation .
  return (isHeap_recursive(arr, 2 * i + 1, n) &&
          isHeap_recursive(arr, 2 * i + 2, n));
}

// Returns 1 if arr[i..n-1] represents a
// min-heap
int isHeap_iter(int arr[], int n) {
  // Start from root and go till the last internal
  // node
  for (int i = 0; i <= (n - 2) / 2; i++) {
    // If left child is smaller, return false
    if (arr[2 * i + 1] < arr[i]) {
      return 0;
    }

    // If right child is smaller, return false // BY THEM SELVES
    if ((2 * i + 2 < n) && (arr[2 * i + 2] < arr[i])) {
      return 0;
    }
  }
  return 1;
}

// Driver program
int main() {
  // create an array of n entried
  int n, *arr;

  // ask for number of entries and scan it
  printf("How many entries? ");
  scanf("%d", &n);

  // malloc the array
  arr = (int *)malloc(n * sizeof(int));

  // read the values in a loop
  printf("Enter %d entries: ", n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  // test cases examples: (remove or keep commented out for submission)
  // int arr[6] = {12, 13, 14, 15, 110, 115}; //it is heap
  // int arr[6] = {12, 110, 14, 15, 13, 115}; // not min heap

  // print results
  if (isHeap_recursive(arr, 0, n))
    printf("Recursive says Yes!\n");
  else
    printf("Recursive says No!\n");

  if (isHeap_iter(arr, n))
    printf("Iterative says Yes!\n");
  else
    printf("Iterative says No!\n");

  free(arr);

  return 0;
}
