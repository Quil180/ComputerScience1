#include <stdio.h>

void printReverse(char string[], int length) {
	// if hello is given and a length of 5, it should print olleh
	if (length != 1) {
		printf("%c", string[length-1]);
		printReverse(string, length-1);
	} else {
		printf("%c", string[0]);
	}
}

int main() {
  printReverse("hello", 5);
  return 0;
}
