#include <stdio.h>
#include <stdlib.h>

typedef struct node { // this is a node of a single linked list.
  int data;           // this holds the data you want to store (can be anything)
  // this points to the next node (which is why it has to be a node *)
  struct node *next; 
} node;

// creating a node structure function
node *createNode (int item) {
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

node *insert_sorted(node *root, int item) {
}

// this function takes an item and insert it in the end of the linked list
node *insert_end(node *root, int item) {
}

/*this function deletes the first occurrence of a given item from linked list.
it returns the updated/original root
*/
node *DelList(node *head, int item) {
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
    printf("\nMenu: 1. insert at the front, 2. insert at the end, 3. Delete, 5.  sorted insert, 4. exit: ");
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
      display(root);
    }

    if (ch == 5) {
      printf("\nEnter data(an integer): ");
      scanf("%d", &ele);

      // call appropriately
      display(root);
    }
  }
  return 0;
}
