#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node { // this is a node of a single linked list.
  int data;           // this holds the data you want to store (can be anything)
  // this points to the next node (which is why it has to be a node *)
  struct node *next;
} node;

// creating a node structure function
node *createNode(int item) {
  node *temp = malloc(sizeof(node));
  temp->data = item;
  temp->next = NULL;

  return temp;
}

// this function takes an item and insert it in the linked list pointed by root.
node *insert_front(node *head, int item) {
  node *temp = createNode(item);

  if (head == NULL) {
    // if the node isnt pointing to anything, point it to the temp one
    head = temp;
    return head;
  } else {
    temp->next = head;
    head = temp;
    return head;
  }

  return head;
}

node *insert_sorted(node *head, int item) {
  node *temp = createNode(item);
  if (head == NULL || head->data > item) {
    temp->next = head;
    head = temp;
    return head;
  }
}

// this function takes an item and insert it in the end of the linked list
node *insert_end(node *head, int item) {
  node *temp = malloc(sizeof(node));
  temp->data = item;
  temp->next = NULL;

  if (head == NULL) {
    // if the list doesnt exist, then temp will start the linked list
    head = temp;
    return head;
  } else {
    // the head/root is already a linked list
    node *walker = head;
    while (walker->next != NULL) {
      walker = walker->next;
    }
    // walker is now in the last element of the linked list
    // so we shall point the last element to the new end we made at the
    // beginning
    walker->next = temp;
  }

  return head;
}

/*this function deletes the first occurrence of a given item from linked list.
it returns the updated/original root
*/
node *DelList(node *head, int item) {
  // we want to delete the item in the linked list
  if (!head) {
    return head;
  }
  // the head was not null and therefore a linked list exists
  if (head->data == item) {
    // the item is at the head
    node *temp = head;
    head = head->next;
    free(temp);
    return head;
  } else {
    // the item is not at head
    node *walker = head;
    // find the address of the element that has the data of value item.
    while (walker->next != NULL && walker->next->data != item) {
      walker = walker->next;
    }
    if (walker->next == NULL) {
      // the item was not found :(
      return head;
    }
    // now we delete the item and rearrange the funny linkedlist
    node *temp = walker->next;
    walker->next = walker->next->next;
    free(temp);
  }
  return head;
}

void display(node *t) {
  printf("\nPrinting your linked list.......");

  while (t != NULL) {
    printf("%d ", t->data);
    t = t->next;
  }

  printf("\n");
}

int main() {
  // declare root apprpriately
  // you must initialize it to NULL
  node *root = NULL;

  int ch, ele, v, del;
  while (1) {
    printf("\nMenu: 1. insert at the front, 2. insert at the end, 3. Delete, "
           "5.  sorted insert, 4. exit: ");
    scanf("%d", &ch);
    if (ch == 4) {
      printf("\nGOOD BYE>>>>\n");
      break;
    }
    if (ch == 1) {
      printf("\nEnter data(an integer): ");
      scanf("%d", &ele);

      root = insert_front(root, ele);

      // call the funtion appropriately
      display(root);
    }
    if (ch == 2) {
      printf("\nEnter information(an integer): ");
      scanf("%d", &ele);

      root = insert_end(root, ele);

      // call the funtion appropriately
      display(root);
    }
    if (ch == 3) {
      printf("\nEnter info which u want to DELETE: ");
      scanf("%d", &del);
      ////call the funtion appropriately ______________________
      DelList(root, del);
      display(root);
    }

    if (ch == 5) {
      printf("\nEnter data(an integer): ");
      scanf("%d", &ele);

      insert_sorted(root, ele);

      // call appropriately
      display(root);
    }
  }
  return 0;
}
