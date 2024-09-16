/*
 * This code is written by Yousef Awad. This code is intended to create
 * linked lists and then rearrange and sort them.
 */
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

// thihs function displays the linked list
void display(node *t) {
  printf("\nPrinting your linked list.......");
  while (t != NULL) {
    printf("%d ", t->data);
    t = t->next;
  }
}

// this function is to add a node to the beginning of the linked list
node *insert_front(node *root, int item) {
  // create the node to be placed at the front
  node *temp = malloc(sizeof(node));
  temp->data = item;
  if (root == NULL) {
    // this is the start of a new linked list
    temp->next = NULL;
    root = temp;
    return root;
  }
  // the linked list already exists there we replace the head of the linked
  // list
  temp->next = root;
  root = temp;
  return root;
};

// this function reverses the order of the linked list
node *reverse(node *head) {
  // check if a linked list exist
  if (head == NULL) {
    return head;
  }
  // since we got this far, we have been given a valid linked list
  node *reverse = head;
  // find the end of the current linked list given
  while (reverse->next != NULL) {
    reverse = reverse->next;
  }
  // we now have the end of the linked list
  node *newhead = reverse;
  // now we want to find the value that points to this node
  node *findthisplease = newhead;
  while (findthisplease != head) {
    reverse = head;
    while (reverse->next != findthisplease) {
      reverse = reverse->next;
    }
    // now we have the node that points to newhead
    findthisplease->next = reverse;
    findthisplease = reverse;
  }
  // findthisplease is therefore same as the original head
  head->next = NULL;
  return newhead;
}

// this function allows the user to place a node in a position not at the start
void insertToPlace(node *head, int val, int place) {
  // making the node we want to place into the linked list
  node *newnode = malloc(sizeof(node));
  newnode->data = val;
  node *temp = head;
  int count = 1;
  if (place <= 1) {
    printf("List is empty or place is not valid\n");
  } else {
    while (temp->next != NULL && count < place - 1) {
      temp = temp->next;
      count += 1;
    }
    // if we get to this point, then we found either the end of the list or the
    // spot we want to put the node in
    newnode->next = temp->next;
    temp->next = newnode;
  }
}

int main() {
  node *root = NULL; // very important line. Otherwise all function will fail
  node *t;
  int ch, ele, v, del;
  while (1) {
    printf("\nMenu: 1. insert at front, 2. reverse list 3. Insert to place 0. "
           "exit: ");
    scanf("%d", &ch);
    if (ch == 0) {
      printf("\nGOOD BYE>>>>\n");
      break;
    }
    if (ch == 1) {
      printf("\nEnter data (an integer): ");
      scanf("%d", &ele);
      root = insert_front(root, ele);
      display(root);
    }
    if (ch == 2) {
      root = reverse(root);
      printf("List reversed.\n");
      display(root);
    }
    if (ch == 3) {
      int place;
      printf("\nEnter data (an integer) and place (>1) separated by space: ");
      scanf("%d %d", &ele, &place);
      insertToPlace(root, ele, place);
      display(root);
    }
  }

  // freeing the memory allocated
  node *temp = root;
  while (temp->next != NULL) {
    node *temp2 = temp->next;
    free(temp);
    temp = temp2;
  }
  free(temp);

  return 0;
}
