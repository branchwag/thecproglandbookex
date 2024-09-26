//write a function undef that will remove a name and a definition from the table maintained by lookup and install

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 101

typedef struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
} NList;

NList *hashtab[HASH_SIZE]; //arry of pointers

unsigned hash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval; //compute hash
  return hashval % HASH_SIZE;
}

NList *install(char *name, char *defn) {
  NList *np = (NList *)malloc(sizeof(*np));
  unsigned hashval;

  if (np == NULL || (np->name = strdup(name)) == NULL || (np->defn = strdup(defn)) == NULL) {
    return NULL;
  }

  hashval = hash(name);
  np->next = hashtab[hashval];
  hashtab[hashval] = np;
  
  return np;
}

//remove name and def
void undef(char *name) {
  unsigned hashval = hash(name);
  NList *np = hashtab[hashval];
  NList *prev = NULL;

  while (np != NULL) {
    if (strcmp(name, np->name) == 0) {
        if (prev == NULL) {
          hashtab[hashval] = np->next;
        } else {
            prev->next = np->next;
        }
        free(np->name);
        free(np->defn);
        free(np);
        return;
    }
    prev = np;
    np = np->next;
  }
  printf("Name '%s' not found.\n", name);
}

void print_table() {
  printf("Symbol Table:\n");
  for (int i = 0; i < HASH_SIZE; i++) {
       NList *np = hashtab[i];
       while (np != NULL) {
          printf(" %s: %s\n", np->name, np->defn);
          np = np->next;
          }
        }
      }

int main() {
  install("x", "10");
  install("y", "20");
  install("z", "30");

  print_table();
  undef("y");
  print_table();

  undef("y");

  undef("x");
  undef("z");

return 0;
}
