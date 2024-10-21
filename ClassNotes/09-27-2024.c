#include <stdio.h>
#include <pthread.h> // for multithreading

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

// permutation functions below
// using a helper method
void permutation(int *givenarray) {
  
}

int main() {
  // recursion
  // example of recursion is a fibonaci number (where the next number is the
  // last 2 numbers added together)
    printf("%d ", f(20));
}
