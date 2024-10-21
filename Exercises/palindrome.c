#include <stdio.h>
#include <string.h>

#define MAX 100

struct stack {
  int top;
  char items[MAX];
};

void init(struct stack *s) { s->top = -1; }

int full(struct stack *s) { return s->top == MAX - 1; }

int empty(struct stack *s) { return s->top == -1; }

void push(struct stack *s, char c) {
  if (full(s)) {
    printf(">>OVERFLOW<<\n");
    return;
  } else {
    s->items[++(s->top)] = c;
  }
}

char pop(struct stack *s) {
  if (empty(s)) {
    printf(">>EMPTY<<\n");
    return '\0';
  } else {
    return s->items[s->top--];
  }
}

int main() {
  char str[MAX];

  printf("Enter a string: ");
  scanf("%s", str);
  int l = strlen(str);

  struct stack stack;
  init(&stack);

  for (int i = 0; i < l; i++) {
    push(&stack, str[i]);
  }
  for (int i = 0; i < l; i++) {
    if (pop(&stack) != str[i]) {
      printf("NOT A PALINDROME.");
      return 0;
    }
  }
  printf("IS A PALINDROME.");

  return 0;
}
