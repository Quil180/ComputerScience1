/* COP 3502C Assignmen t 5
This program is written by: Kevin Maa */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node struct
typedef struct Node {
  char name[26];
  int fine;
  struct Node *left, *right;
} Node;

// Create node
Node *createNode(const char *name, int fine) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  strcpy(newNode->name, name);
  newNode->fine = fine;
  newNode->left = newNode->right = NULL;
  return newNode;
}

Node *add(Node *root, const char *name, int fine, int *depth) {
  if (root == NULL) {
    Node *newNode = createNode(name, fine);
    printf("%s %d %d\n", name, fine, *depth);
    return newNode;
  } else {
    int cmp = strcmp(name, root->name);

    if (cmp > 0) {
      (*depth)++;
      root->right = add(root->right, name, fine, depth);
    } else if (cmp < 0) {
      (*depth)++;
      root->left = add(root->left, name, fine, depth);
    } else {
      root->fine += fine;
      printf("%s %d %d\n", root->name, root->fine, *depth);
    }

    return root;
  }
}

// Find node
Node *search(Node *current_ptr, const char *name, int *depth) {
  if (current_ptr != NULL) {
    if (strcmp(current_ptr->name, name) == 0)
      return current_ptr;
    (*depth)++;
    if (strcmp(name, current_ptr->name) < 0)
      return search(current_ptr->left, name, depth);
    else
      return search(current_ptr->right, name, depth);
  }
  return NULL;
}

// Check if node is leaf
int isLeaf(Node *node) { return (node->left == NULL && node->right == NULL); }

// Check if node has only left child
int hasOnlyLeftChild(Node *node) {
  return (node->left != NULL && node->right == NULL);
}

// Check if node has only right child
int hasOnlyRightChild(Node *node) {
  return (node->left == NULL && node->right != NULL);
}

// Find parent of given node
Node *parent(Node *root, Node *node) {
  if (root == NULL || root == node)
    return NULL;
  if (root->left == node || root->right == node)
    return root;
  if (strcmp(node->name, root->name) < 0)
    return parent(root->left, node);
  else
    return parent(root->right, node);
}

// Find node with min val in subtree
Node *minVal(Node *root) {
  if (root->left == NULL)
    return root;
  else
    return minVal(root->left);
}

// Find node with max val in subtree
Node *maxVal(Node *root) {
  if (root->right == NULL)
    return root;
  else
    return maxVal(root->right);
}

// deletes node
Node *deleteNode(Node *root, const char *name) {
  if (root == NULL) {
    return root;
  }

  int cmp = strcmp(name, root->name);
  if (cmp < 0) {
    root->left = deleteNode(root->left, name);
  } else if (cmp > 0) {
    root->right = deleteNode(root->right, name);
  } else {
    if (isLeaf(root)) {
      free(root);
      return NULL;
    } else if (hasOnlyLeftChild(root)) {
      Node *temp = root->left;
      free(root);
      return temp;
    } else if (hasOnlyRightChild(root)) {
      Node *temp = root->right;
      free(root);
      return temp;
    } else {
      Node *temp = maxVal(root->left);
      strcpy(root->name, temp->name);
      root->fine = temp->fine;
      root->left = deleteNode(root->left, temp->name);
    }
  }
  return root;
}

Node *deductFine(Node *root, const char *name, int fine) {
  int depth = 0;
  Node *target = search(root, name, &depth);
  if (target != NULL) {
    target->fine -= fine;
    if (target->fine <= 0) {
      printf("%s removed\n", name);
      root = deleteNode(root, name);
    } else {
      printf("%s %d %d\n", name, target->fine, depth);
    }
  } else {
    printf("%s not found\n", name);
  }
  return root;
}

// Calc height of subtree
int calculateHeight(Node *root) {
  if (root == NULL) {
    return -1;
  }
  int leftHeight = calculateHeight(root->left);
  int rightHeight = calculateHeight(root->right);
  return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Determine if tree is balanced
void heightBalance(Node *root) {
  if (root == NULL) {
    printf("The tree is empty\n");
    return;
  }
  int leftHeight = calculateHeight(root->left);
  int rightHeight = calculateHeight(root->right);
  if (leftHeight == rightHeight) {
    printf("left height = %d right height = %d balanced\n", leftHeight,
           rightHeight);
  } else {
    printf("left height = %d right height = %d not balanced\n", leftHeight,
           rightHeight);
  }
}

// Calc total fine below given name
int calcBelow(Node *root, const char *name) {
  if (root == NULL) {
    return 0;
  }
  int sum = 0;
  if (strcmp(root->name, name) <= 0) {
    sum += root->fine;
    sum += calcBelow(root->left, name);
    sum += calcBelow(root->right, name);
  } else {
    sum += calcBelow(root->left, name);
  }
  return sum;
}

void calculateTotalFineAndCount(Node *root, double *totalFine, int *count) {
  if (root == NULL) {
    return;
  }
  calculateTotalFineAndCount(root->left, totalFine, count);
  *totalFine += root->fine;
  (*count)++;
  calculateTotalFineAndCount(root->right, totalFine, count);
}

// Calc avg fine amount per node
double calculateAverage(Node *root, int *count) {
  if (root == NULL) {
    return 0.0;
  }
  double totalFine = 0.0;
  *count = 0;
  calculateTotalFineAndCount(root, &totalFine, count);
  if (*count == 0) {
    return 0.0;
  }
  return totalFine / *count;
}

// Free all nodes
void freeTree(Node *root) {
  if (root == NULL) {
    return;
  }
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

int main() {
  Node *root = NULL;
  int depth;

  char command[50], name[26];
  int value;

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", command);
    if (strcmp(command, "add") == 0) {
      scanf("%s %d", name, &value);
      depth = 0;
      root = add(root, name, value, &depth);
    } else if (strcmp(command, "deduct") == 0) {
      scanf("%s %d", name, &value);
      root = deductFine(root, name, value);
    } else if (strcmp(command, "search") == 0) {
      depth = 0;
      scanf("%s", name);
      Node *foundNode = search(root, name, &depth);
      if (foundNode != NULL) {
        printf("%s %d %d\n", name, foundNode->fine, depth);
      } else {
        printf("%s not found\n", name);
      }
    } else if (strcmp(command, "height_balance") == 0) {
      heightBalance(root);
    } else if (strcmp(command, "calc_below") == 0) {
      scanf("%s", name);
      int totalFine = calcBelow(root, name);
      printf("%d\n", totalFine);
    } else if (strcmp(command, "average") == 0) {
      int count;
      double avg = calculateAverage(root, &count);
      printf("%.2f\n", avg);
    }
  }

  // Free all nodes
  freeTree(root);

  return 0;
}
