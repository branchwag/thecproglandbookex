#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

void fold_line(const char *line, int max_width);

int main(int argc, char *argv[]) {
  int max_width = 80;

  if (argc > 1) {
    max_width = atoi(argv[1]);
    if (max_width <= 0) {
      fprintf(stderr, "Invalid column width. Using default width of 80.\n");
      max_width = 80;
    }
  }

  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), stdin)) {
   line[strcspn(line, "\n")] = '\0';
   fold_line(line, max_width);
  }
  return 0;
}

void fold_line(const char *line, int max_width) { 
  int length = strlen(line);
  int start = 0;

  while (start < length) {
    int end = start + max_width;
    
    if(end >= length) {
      printf("%s\n", line + start);
      break;
    }

 int break_pos = end;

while (break_pos > start && !isspace(line[break_pos])) {
  --break_pos;
}

if (break_pos == start) {
  break_pos = end;
  if (break_pos > length) {
    break_pos = length;
  }
} else {
    break_pos++;
}

printf("%.*s\n", break_pos - start, line + start);

start = break_pos;

while (start < length && isspace(line[start])) {
  start++;
    }
  }
}
