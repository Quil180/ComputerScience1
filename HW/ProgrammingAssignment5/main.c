/* COP 3502C Assignment 5
This program is written by: Yousef Alaa Awad */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char name[26];
  int fine;
  struct node *left;
  struct node *right;
} node;

node *createNode(char name[26], int fine) {
  node *temp = (node *)malloc(sizeof(node));
  strcpy(temp->name, name);
  temp->fine = fine;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

node *search(node *root, const char *name, int *depth) {
  if (root != NULL) {
    if (strcmp(root->name, name) == 0) {
      return root;
    }
    (*depth)++;
    if (strcmp(name, root->name) < 0) {
      return search(root->left, name, depth);
    } else {
      return search(root->right, name, depth);
    }
  }
  return NULL;
}

node *add(node *root, char name[26], int money, int *depth) {
  if (root == NULL) {
    // the tree doesn't exist in the first place.
    node *temp = createNode(name, money);
    printf("%s %d %d\n", name, money, *depth);
    return temp;
  } else {
    if (strcmp(name, root->name) > 0) {
      (*depth)++;
      root->right = add(root->right, name, money, depth);
    } else if (strcmp(name, root->name) < 0) {
      (*depth)++;
      root->left = add(root->left, name, money, depth);
    } else {
      root->fine += money;
      printf("%s %d %d\n", root->name, root->fine, *depth);
    }
  }

  // return the head of the node o7
  return root;
}

node *searchParent(node *wefind, node *root) {
  if (root == NULL || root == wefind) {
    return NULL;
  }
  if (root->left == wefind || root->right == wefind) {
    return root;
  }
  if (strcmp(wefind->name, root->name) < 0) {
    return searchParent(wefind, root->left);
  } else {
    return searchParent(wefind, root->right);
  }
}

node *minVal(node *root) {
  if (root->left == NULL) {
    return root;
  } else {
    return minVal(root->left);
  }
}

node *maxVal(node *root) {
  if (root->right == NULL) {
    return root;
  } else {
    return maxVal(root->right);
  }
}

node *delete(node *root, char name[26]) {
  if (root == NULL) {
    return root;
  }

  if (strcmp(name, root->name) < 0) {
    root->left = delete (root->left, name);
  } else if (strcmp(name, root->name) > 0) {
    root->right = delete (root->right, name);
  } else {
    // we are on the right node.
    if (root->left == NULL && root->right == NULL) {
      free(root);
      return NULL;
    } else if (root->left != NULL && root->right == NULL) {
      node *temp = root->left;
      free(root);
      return temp;
    } else if (root->left == NULL && root->right != NULL) {
      node *temp = root->right;
      free(root);
      return temp;
    } else {
      node *temp = maxVal(root->left);
      strcpy(root->name, temp->name);
      root->fine = temp->fine;
      root->left = delete (root->left, temp->name);
    }
  }
  return root;
}

node *deduct(node *root, char name[26], int fine) {
  int depth = 0;
  node *found = search(root, name, &depth);
  if (found != NULL) {
    found->fine -= fine;
    if (found->fine <= 0) {
      printf("%s removed\n", name);
      root = delete (root, name);
    } else {
      printf("%s %d %d\n", name, found->fine, depth);
    }
  } else {
    printf("%s not found\n", name);
  }
  return root;
}

int calcHeight(node *root) {
  if (root == NULL) {
    return -1;
  }

  int left = calcHeight(root->left);
  int right = calcHeight(root->right);

  if (left > right) {
    return 1 + left;
  }
  return 1 + right;
}

void balance(node *root) {
  if (root == NULL) {
    printf("The tree is empty\n");
    return; // the tree was empty
  }
  int left = calcHeight(root->left);
  int right = calcHeight(root->right);
  printf("left height = %d right height = %d ", left, right);
  if (left == right) {
    printf("balanced\n");
  } else {
    printf("not balanced\n");
  }
}

int belowCalc(node *root, char *name) {
  if (root == NULL) {
    return 0;
  }
  int sum = 0;
  if (strcmp(root->name, name) <= 0) {
    sum += root->fine;
    sum += belowCalc(root->left, name);
    sum += belowCalc(root->right, name);
  } else {
    sum += belowCalc(root->left, name);
  }
  return sum;
}

int sum(node *current) {
  if (current != NULL) {
    return current->fine + sum(current->left) + sum(current->right);
  } else {
    return 0;
  }
}

int numNodes(node *root) {
  if (root == NULL) {
    return 0;
  }
  return 1 + numNodes(root->left) + numNodes(root->right);
}

double average(node *root) {
  int add = sum(root);
  int count = numNodes(root);
  return 1.0 * add / count;
}

void freeAll(node *root) {
  if (root == NULL) {
    return;
  }
  freeAll(root->left);
  freeAll(root->right);
  free(root);
}

int main() {
  int commands = -1;
  scanf("%d", &commands);

  // making an empty root :p
  node *root = NULL;
  int depth;
  char name[26];
  int fine;

  for (int i = 0; i < commands; i++) {
    // for every command, check what the command name is.
    char command[11] = "";
    scanf("%s", command);
    // checking which command we got:
    if (strcmp(command, "add") == 0) {
      // we are doing the add command.
      fine = 0;
      depth = 0;
      // getting the data from the input.
      scanf("%s %d", name, &fine);
      // actually adding the data to the tree.
      root = add(root, name, fine, &depth);
    } else if (strcmp(command, "deduct") == 0) {
      // we are doing the deduct command.
      scanf("%s %d", name, &fine);
      root = deduct(root, name, fine);
    } else if (strcmp(command, "search") == 0) {
      // we are doing the search command.
      depth = 0;
      scanf("%s", name);
      node *found = search(root, name, &depth);
      if (found != NULL) {
        printf("%s %d %d\n", name, found->fine, depth);
      } else {
        printf("%s not found\n", name);
      }
    } else if (strcmp(command, "average") == 0) {
      printf("%.2f\n", average(root));
      // we are doing the average command.
    } else if (strcmp(command, "height_balance") == 0) {
      balance(root);
    } else if (strcmp(command, "calc_below") == 0) {
      // we are doing the calc_below command.
      scanf("%s", name);
      int below = belowCalc(root, name);
      printf("%d\n", below);
    }
  }

  freeAll(root);

  return 0;
}
