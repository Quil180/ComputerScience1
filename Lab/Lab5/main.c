// In this code we will use stack to check the balance of parentheses.

#include <ctype.h> // needed for isdigit
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The array will store the items in the stack, first in
// index 0, then 1, etc. top will represent the index
// to the top element in the stack. If the stack is
// empty top will be -1.

#define SIZE 100
#define EMPTY -1

struct stack {
  char items[SIZE];
  int top;
};

void initialize(struct stack *stackPtr);
int full(struct stack *stackPtr);
int push(struct stack *stackPtr, char value);
int empty(struct stack *stackPtr);
char pop(struct stack *stackPtr);
int peek(struct stack *stackPtr);
void print_stack(struct stack *stackPtr);

// functions you have to complete:
int checkBalance(char exp[]);

int priority(char ch);
int isOperator(char ch);
char *infixToPostfix(char infix[]);
int isParentheses(char ch1);

int main(void) {
  int ch;
  char exp[SIZE], c;

  int valid;

  printf("\nEnter Expression: ");
  scanf("%[^\n]s", exp);

  printf("Your input expression: %s\n", exp);

  valid = checkBalance(exp);

  if (valid) {
    char *postfix = infixToPostfix(exp);
    printf("The postfix is: %s\n", postfix);

    free(postfix);
  }

  return 0;
}

int checkBalance(char exp[]) {
  int valid = 1;
  struct stack mine;

  // Set up the stack and push a couple items, then pop one.
  initialize(&mine);

  printf("\nChecking balance...\n");
  for (int i = 0; exp[i] != '\0'; i++) {
    // while i is not at the end of the expression given, do the following.

    if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') {
      // if the current character is a opening bracket, push it into the stack.
      push(&mine, exp[i]);
    } else if (exp[i] == ')') {
      // if we find a exit paranthesis, pop it out of the stack.
      char a = pop(&mine);
      if (a == 'I' || a != '(') {
        // and check if there is an accompanying (. since we are here, it was
        // not found.
        valid = 0;
        printf("INVALID for )!!!\n");
        return valid;
      }
    } else if (exp[i] == '}') {
      // if given a }. then check if it has an accompanying {.
      char a = pop(&mine);
      if (a == 'I' || a != '{') {
        // a { was not found, meaning the expression is invalid.
        valid = 0;
        printf("INVALID for }!!!\n");
        return valid;
      }
    } else if (exp[i] == ']') {
      // if a ] is found, look in the stack to see if an accompanying [ is
      // found.
      char a = pop(&mine);
      if (a == 'I' || a != '[') {
        // a [ was not found and therefore the expression is invalid.
        valid = 0;
        printf("INVALID for ]!!!\n");
        return valid;
      }
    }
  }
  if (pop(&mine) != 'I') {
    // if the stack isnt empty, as at this point we have finished the
    // expression, then the whole expression is invalid.
    valid = 0;
    printf("INVALID. You have extra!!!\n");
  }
  if (valid == 1) {
    // the whole expression is valid!
    printf("VALID\n");
  }
  // returning if the expression is valid or not.
  return valid;
}

void print_stack(struct stack *stackPtr) {
  for (int i = 0; i <= stackPtr->top; i++)
    printf("%c-->", stackPtr->items[i]);

  printf("\n");
}

void initialize(struct stack *stackPtr) { stackPtr->top = -1; }

// If the push occurs, 1 is returned. If the
// stack is full and the push can't be done, 0 is
// returned.
int push(struct stack *stackPtr, char value) {

  // Check if the stack is full.
  if (full(stackPtr))
    return 0;

  // Add value to the top of the stack and adjust the value of the top.
  stackPtr->items[stackPtr->top + 1] = value;
  (stackPtr->top)++;
  return 1;
}

// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack *stackPtr) { return (stackPtr->top == SIZE - 1); }

// Returns true iff the stack pointed to by stackPtr is empty.
int empty(struct stack *stackPtr) { return (stackPtr->top == -1); }

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is popped and returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char pop(struct stack *stackPtr) {

  char retval;

  // Check the case that the stack is empty.
  if (empty(stackPtr))
    return 'I';

  // Retrieve the item from the top of the stack, adjust the top and return
  // the item.
  retval = stackPtr->items[stackPtr->top];
  (stackPtr->top)--;
  return retval;
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
int peek(struct stack *stackPtr) {

  // Take care of the empty case.
  if (empty(stackPtr))
    return EMPTY;

  // Return the desired item.
  return stackPtr->items[stackPtr->top];
}

char *infixToPostfix(char infix[]) {
  struct stack operaters;
  initialize(&operaters);

  int count = 0;
  // times 2 due to spaces inbetween
  char *postfix = (char *)malloc(strlen(infix + 1) * sizeof(char) * 2);

  for (int i = 0; i < strlen(infix); i++) {
    if (isdigit(infix[i])) {
      while (isdigit(infix[i])) {
        // a digit was found in the stack, therefore we push it to the postfix
        // immediately.
        postfix[count] = infix[i];
        i++;
        count++;
      }
      // resetting the i index.
      i--;
      postfix[count] = ' ';
      count++;
    } else if (isOperator(infix[i])) {
      // an operator was found, and not a digit :(
      if (empty(&operaters)) {
        // if the operators stack is empty, then immediately just push the found
        // operator
        push(&operaters, infix[i]);
      } else if (priority(infix[i]) > priority(peek(&operaters))) {
        // if the operator stack isnt empty, then check if the priority of the
        // operator found is higher than the current one.
        push(&operaters, infix[i]);
      } else {
        // if none of the other conditions are met, try the following as
        // insurance
        while (!empty(&operaters) &&
               priority(infix[i]) <= priority(peek(&operaters)) &&
               !isParentheses(peek(&operaters))) {
          // if the operators stack isnt full, and the priority found for the
          // operator found is less than the one in the operators stack, and its
          // not a paranthesis in the operator stack. then do the following.
          postfix[count] = pop(&operaters);
          count++;
          postfix[count] = ' ';
          count++;
        }
        push(&operaters, infix[i]);
      }
    } else if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[') {
      // if the current character is a beginning paranthesis, then just push it
      // to the operator stack.
      push(&operaters, infix[i]);
    } else if (infix[i] == ')' || infix[i] == '}' || infix[i] == ']') {
      // if its the closing paranthesis, then check to see if a opening version
      // exists in the operator stack. If not, cry as that means the checking
      // function broke.
      while (!empty(&operaters) && peek(&operaters) != '(' &&
             peek(&operaters) != '{' && peek(&operaters) != '[') {
        postfix[count++] = pop(&operaters);
        postfix[count++] = ' ';
      }
      pop(&operaters);
    }
  }

  // last minute checks
  while (!empty(&operaters)) {
    // if the operators stack isnt empty, then pop the rest into the postfix.
    postfix[count++] = pop(&operaters);
    postfix[count++] = ' ';
  }
  // add a terminating character, to signal the end of the string, then return
  // the finished postfix.
  postfix[count] = '\0';
  return postfix;
}

// returns the priority of the passed character
// (  {  [  : 0
// + - : 1
// * / %: 2
// ^ : 3
int priority(char ch) {
  if (ch == '(' || ch == '{' || ch == '[')
    return 0;
  if (ch == '+' || ch == '-')
    return 1;
  if (ch == '*' || ch == '/' || ch == '%')
    return 2;
  if (ch == '^')
    return 3;
}

// returns 1 of ch is an operator + - * / ^ %
// returns 0 otherwise
int isOperator(char ch) {
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
      ch == '%') {
    return 1;
  }
  return 0;
}

// parentheses check
//  returns 1 of ch is a parentheses { [ ( ) ] }
//  returns 0 otherwise
int isParentheses(char ch1) {
  if (ch1 == '{' || ch1 == '[' || ch1 == '(' || ch1 == ')' || ch1 == ']' ||
      ch1 == '}')
    return 1;
  return 0;
}
