//print distinct words from input sorted - decreasing occurrence. Count before word.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDS 1000
#define MAXWORDLEN 100

struct WordCount {
  char word[MAXWORDLEN];
  int count;
};

int compare(const void *a, const void *b) {
  struct WordCount *wordCountA = (struct WordCount *)a;
  struct WordCount *wordCountB = (struct WordCount *)b;
  return wordCountB->count - wordCountA->count;
}

int main() {
  struct WordCount words[MAXWORDS];
  int numWords = 0;
  char word[MAXWORDLEN];

  while (scanf("%99s", word) == 1) {
      int found = 0;
      for (int i = 0; i < numWords; i++) {
        if (strcmp(words[i].word, word) == 0) {
           words[i].count++;
           found = 1;
           break;
     }
  }

    if (!found && numWords < MAXWORDS) {
      strcpy(words[numWords].word, word);
      words[numWords].count = 1;
      numWords++;
    }
  }

    qsort(words, numWords, sizeof(struct WordCount), compare);
    for (int i = 0; i < numWords; i++) {
        printf("%d %s\n", words[i].count, words[i].word);
    }

  return 0;
}
