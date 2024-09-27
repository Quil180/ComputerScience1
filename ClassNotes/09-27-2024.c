#include <stdio.h>

int fibonacci(int n) {
  if (n <= 1) {
    return n;
  } else {
    return (fibonacci(n - 1) + fibonacci(n - 2));
  }
}

int f(int n) {
  int ans, i;
  if (n < 3) {
    return n;
  }
  ans = f(n / 2);
  for (i = 0; i < n; i++) {
    ans += f(i);
  }
  return ans;
}

int main() {
  // recursion
  // example of recursion is a fibonaci number (where the next number is the
  // last 2 numbers added together)
    printf("%d ", f(35));
}
