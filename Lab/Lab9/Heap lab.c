/* COP 3502C Heap Lab
This program is written by: Kevin Maa */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// GOAL: In this lab we will write a code that will check whether an array represents a minheap or not.

int isHeap_recursive(int arr[], int i, int n)
{
	// if i is outside of the array range, it means this part is a heap because we already confirmed that all nodes are valid
	if (i >= n || n <= 0)
		return 1;

	// if there is a left child, compare with it
	if ((2 * i + 1) < n) // is the left child index within the range, do we have a left child?
		if (arr[2 * i + 1] < arr[i]) // if we have a left child, is the value of it less than the current node?
			return 0; // left child is smaller, what's the result? is this a min heap?

	// if there is a right, compare with it
	if ((2 * i + 2) < n) // is the right child index within the range, do we have a right child?
		if (arr[2 * i + 2] < arr[i]) // if we have a right child, is the value of it less than the current node?
			return 0; // right child is smaller, what's the result? is this a min heap?

	// recursively go to the left and right child and return the final result based on && operation
	return (isHeap_recursive(arr, 2 * i + 1, n) && isHeap_recursive(arr, 2 * i + 2, n));
}

// Returns 1 if arr[i..n-1] represents a min-heap
int isHeap_iter(int arr[], int n)
{
	// Start from root and go till the last internal node
	for (int i = 0; i <= (n - 2) / 2; i++) // last internal node is at (n-2)/2
	{
		// If left child is smaller, return false
		if (arr[2 * i + 1] < arr[i]) // is value at left child smaller?
			return 0; // if yes, this is not a min heap

		// If right child exists and is smaller, return false
		if (2 * i + 2 < n && arr[2 * i + 2] < arr[i]) // right child exists and right child is smaller than current node
			return 0; // if yes, this is not a min heap
	}
	return 1; // if we checked all nodes are valid, then it is a min heap
}

// Driver program
int main()
{
	// create an array of n entries
	int n, *arr;

	// ask for number of entries and scan it
	printf("How many entries? ");
	scanf("%d", &n);

	// malloc the array
	arr = (int *)malloc(n * sizeof(int));

	// read the values in a loop
	printf("Enter %d entries: ", n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	// test cases examples: (remove or keep commented out for submission)
	// int arr[6] = {12, 13, 14, 15, 110, 115}; // it is heap
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

	// free allocated memory
	free(arr);

	return 0;
}
