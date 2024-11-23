#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 2000000

struct trie {
  int node_freq;
  int sum_prefix;
  int child_max_freq;
  struct trie *next[26];
};

struct trie *init() {

  // Create the struct, not a word.
  struct trie *myTree = malloc(sizeof(struct trie));
  myTree->node_freq = 0;
  myTree->sum_prefix = 0;
  myTree->child_max_freq = 0;

  // Set each pointer to NULLL.
  int i;
  for (i = 0; i < 26; i++) {
    myTree->next[i] = NULL;
  }

  // Return a pointer to the new root.
  return myTree;
}

void insert(struct trie *tree, char word[], int current_length, int frequency) {
  // no matter if it had to be initialized or not.
  tree->sum_prefix += frequency;

  if (current_length == strlen(word)) {
    // if we are at the end of the word, then add the word frequency.
    tree->node_freq += frequency;
    return;
  }

  // See if the next place to go exists, if not, create it.
  int nextIndex = word[current_length] - 'a';
  if (tree->next[nextIndex] == NULL) {
    tree->next[nextIndex] = init();
  }

  // if the current child_max_frequency is smaller than the new
  // child_max_frequency after we do the next character, replace it with the
  // right one.
  if (tree->child_max_freq < tree->next[nextIndex]->sum_prefix + frequency) {
    tree->child_max_freq = tree->next[nextIndex]->sum_prefix + frequency;
  }

  // go to the next letter of the word given.
  insert(tree->next[nextIndex], word, current_length + 1, frequency);
}

char *query(struct trie *tree, char word[], char _return[], int curr_len) {
  if (curr_len == strlen(word)) {
    // so long as we are at the end of the word we want to search for.
    for (int i = 0; i < 26; i++) {
      // check every letter in the english alphabet if they are existing in the
      // trie, and also if they are the most likely next candidate.
      if (tree->next[i] == NULL) {
        continue;
      }
      if (tree->child_max_freq == tree->next[i]->sum_prefix) {
        // since the letter we are on is the most likely candidate, put it into
        // the buffer of _return
        char c[2] = {'a' + i, '\0'};
        strcat(_return, c);
      }
    }
    if (!strcmp(_return, "")) {
      // if _return was never touched, return a NULL value.
      return NULL;
    }
    // if the previous case doesn't return, we have a valid buffer to return.
    return _return;
  }

  // If the next place doesn't exist, the word isn't isn't valid
  int nextIndex = word[curr_len] - 'a';
  if (tree->next[nextIndex] == NULL) {
    return NULL;
  }

  // if we get this far then we want to go to the next letter of the given word.
  return query(tree->next[nextIndex], word, _return, curr_len + 1);
}

// this function was taken directly from the trie.c in the files of the
// webcourse.
void freeDictionary(struct trie *tree) {
  // Just frees all the memory pointed to by tree (directly and indirectly)
  for (int i = 0; i < 26; i++) {
    if (tree->next[i] != NULL) {
      freeDictionary(tree->next[i]);
    }
  }
  free(tree);
}

int main() {
  // declaration of variables
  int num_commands = 0;              // number of commands.
  int command = 0;                   // the command we want to do.
  int frequency = 0;                 // the amount of a word to add.
  char word[MAXLEN];                 // the word to add.
  char buffer[MAXLEN];               // the buffer for searching.
  struct trie *fuzzyFinder = init(); // the trie proper.

  // finding the amount of commands we want to do.
  scanf("%d", &num_commands);

  for (int i = 0; i < num_commands; i++) {
    // find the command we want to do
    scanf("%d", &command);

    if (command == 1) {
      // we are inserting a word into the trie.
      scanf("%s %d", word, &frequency);
      // insert the word (frequency) amount of times.
      insert(fuzzyFinder, word, 0, frequency);
      // continue to the next command and ignore the rest of the for loop.
      continue;
    }

    // if we get this far, then we can only be searching for a word.
    scanf("%s", word);

    // do the word prediction then print it out.
    if (query(fuzzyFinder, word, buffer, 0)) {
      printf("%s\n", buffer);
      // clear the c buffer
      strcpy(buffer, "");
      continue;
    }

    // we did not find the word or was given an invalid command.
    printf("unrecognized prefix\n");
  }

  // freeing the entire trie.
  freeDictionary(fuzzyFinder);

  // ending the program as it was succesfull.
  return 0;
}
