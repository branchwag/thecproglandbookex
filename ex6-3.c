//create cross-referencer that prints a list of all words in a doc
//and for each word a list of the line numbers on which it occurs
//remove noise words like 'the' 'and'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXLINE 1000
#define MAXNOISE 20

typedef struct {
  char word[MAXWORD];
  int *lines;
  int line_count;
} WordEntry;

WordEntry *table[MAXWORD]; //hashtable
int table_size = 0;

const char *noise_words[MAXNOISE] = {
    "the", "and", "a", "an", "is", "it", "in", "to", "of", "on",
    "for", "with", "as", "by", "that", "this", "but", "are", "was", "were"
};

int is_noise_word(const char *word) {
  for (int i = 0; i < MAXNOISE; i++) {
       if (strcmp(word, noise_words[i]) == 0) {
         return 1;
       }
    }
    return 0;
}

void str_to_lower(char *str) {
  for (int i = 0; str[i]; i++) {
       str[i] = tolower((unsigned char)str[i]);
  }
}

void add_word(const char *word, int line_num) {
  for (int i = 0; i < table_size; i++) {
       if (strcmp(table[i]->word, word) == 0) {
         for (int j = 0; j < table[i]->line_count; j++) {
            if (table[i]->lines[j] == line_num) {
                return;
            }
          }
          table[i]->lines[table[i]->line_count++] = line_num;
          return;
       }
  }

  WordEntry *new_entry = malloc(sizeof(WordEntry));
  strcpy(new_entry->word, word);
  new_entry->lines = malloc(MAXLINE * sizeof(int));
  new_entry->lines[0] = line_num;
  new_entry->line_count = 1;
  table[table_size++] = new_entry;
}

void print_table() {
  for (int i = 0; i < table_size; i++) {
       printf("%s: ", table[i]->word);
       for (int j = 0; j < table[i]->line_count; j++) {
          printf("%d ", table[i]->lines[j]);
        }
        printf("\n");
    }
  }

int main() {
  char line[MAXLINE];
  char word[MAXWORD];
  int line_num = 0;

  while (fgets(line, sizeof(line), stdin)) {
    line_num++;
    char *ptr = line;
    while (sscanf(ptr, "%s", word) == 1) {
        str_to_lower(word);
        if (!is_noise_word(word)) {
          add_word(word, line_num);
        }
        while (*ptr != '\0' && !isspace(*ptr)) {
          ptr++;
        }
        while (*ptr != '\0' && isspace(*ptr)) {
          ptr++;
        }
    }
  }
  
  print_table();

  for (int i = 0; i < table_size; i++) {
       free(table[i]->lines);
       free(table[i]);
  }

return 0;
}
