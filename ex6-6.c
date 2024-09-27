//implement define processor for C programs based on this section

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
#define MAXMACROS 100
#define MAXNAME 100
#define MAXVALUE 100

struct Macro {
    char name[MAXNAME];
    char value[MAXVALUE];
};

struct Macro macros[MAXMACROS];
int macro_count = 0;

void add_macro(const char *name, const char *value) {
  if (macro_count < MAXMACROS) {
      strncpy(macros[macro_count].name, name, MAXNAME);
      strncpy(macros[macro_count].value, value, MAXVALUE);
      macro_count++;
  } else {
      fprintf(stderr, "Max macro limit reached\n");
  }
}

const char *get_macro_value(const char *name) {
  for (int i = 0; i < macro_count; i++) {
       if (strcmp(macros[i].name, name) == 0) {
          return macros[i].value;
       }
    }
    return NULL;
}

void process_line(char *line) {
  char name[MAXNAME];
  char value[MAXVALUE];

  if (sscanf(line, "#define %s %[^\n]", name, value) == 2) {
    add_macro(name, value);
  } else {
    char *token = strtok(line, " \t\n");
    while (token != NULL) {
      const char *macro_value = get_macro_value(token);
      if (macro_value != NULL) {
          printf("%s ", macro_value);
      } else {
          printf("%s ", token);
      }
      token = strtok(NULL, " \t\n");
    }
    printf("\n");
   }
}

int main() {
  char line[MAXLINE];
  printf("Enter lines of code (Ctrl+D to end):\n");
  while (fgets(line, sizeof(line), stdin) != NULL) {
    process_line(line);
  }

  return 0;
}
