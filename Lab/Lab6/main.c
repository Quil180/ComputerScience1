#include <stdio.h>
#include <stdlib.h>
#include "leak_detector_c.h"

struct node {
  int data;
  struct node *next;
};

struct node *insert(struct node *list, int d) {
  // must be recursive.
  if (list == NULL || d <= list->data) { // base case.
    // the list is empty, so no sorting is nessecary.
    struct node *newnode = malloc(sizeof(struct node));
    // initializing the front of the linked list.
    newnode->data = d;
    // setting the newnode's next to be the list.
    // if list is empty, then itll point to null.
    newnode->next = list;
    return newnode; // the list is now newnode
  }
  // if we get this far, then the list is not empty or we haven't found a spot
  // to put the data, and there we must find a spot to put the data into,
  // sorted.
  list->next = insert(list->next, d);
  return list;
};

struct node *del(struct node *list, int d) {
  if (list == NULL) {
    // the list is empty
    return NULL;
  }
  // the list is not empty
  if (list->data == d) {
    // we found the corrent item to delete.
    struct node *temp = list;
    list = list->next;
    // getting rid of the item and returning the subsequent list.
    free(temp);
    return list;
  }
  // we did not find the correct item to delete.
  list->next = del(list->next, d);
  // return the list after this function, as we are done.
  return list;
};

void print(struct node *list) {
  if (list == NULL) {
    // the list is empty
    return;
  }
  // the list is not empty so we shall print our current number then call the
  // function again with the next data element.
  printf("->%d", list->data);
  print(list->next);
}

void freeList(struct node *list) {
  if (list == NULL || list->next == NULL) {
    // the list is empty
    free(list);
    return;
  }
  freeList(list->next);
  free(list);
}

void copy(struct node *source, struct node **destination) {
  if (source != NULL) {
    // the list is not empty.

    // allocating the memory for the destination.
    *destination = malloc(sizeof(struct node));
    // copying the data of the current source data.
    (*destination)->data = source->data;
    // setting the next to null (initializing it)
    (*destination)->next = NULL;

    // recursive part :(
    copy(source->next, &((*destination)->next));
  }
}

int main() {
  atexit(report_mem_leak);
  int number = 0, choice = 0;
  struct node *pList = NULL;
  struct node *nList = NULL;
  // Let the user add values until they enter -1.
  while (choice != 4) {
    // Get the operation.
    printf("\nDo you want to (1)insert, (2)delete, (3)Copy (4)quit.\n");
    scanf("%d", &choice);
    printf("Your choice is %d\n", choice);
    // Execute the operation.
    if (choice == 1) {
      // Get the number.
      printf("Enter the value to insert\n");
      scanf("%d", &number);
      pList = insert(pList, number);
      // Look at the list.
      printf("Items in linked list: ");
      print(pList);
      // printf("\n");
    } else if (choice == 2) { // Get the number.
      printf("Enter the value to delete.\n");
      scanf("%d", &number);
      pList = del(pList, number);
      // Look at the list.
      printf("Items in linked list: ");
      print(pList);
      // printf("\n");
    } else if (choice == 3) {
      if (nList)
        freeList(nList);
      copy(pList, &nList); // passing reference of nList as it is not
      // return anything. Look at the list.
      printf("Items in NEW linked list: ");
      print(nList);
      // printf("\n");
    } else {
      break;
    }
  }
  freeList(nList);
  freeList(pList);
  printf("\nBye..\n");
  return 0;
}
