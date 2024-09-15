//used to read a line of text from input
#include <stdio.h> //fgetc
#include <stdlib.h>

#define MAXLINE 1000

int my_getline(char **lineptr, size_t *n, FILE *stream) {
  size_t len = 0;
  int c;
  char *buffer = NULL;

  if (*lineptr == NULL) {
    *lineptr = malloc(MAXLINE);
    if (*lineptr == NULL) return -1;
    *n = MAXLINE;
  }

  buffer = *lineptr;

  while ((c = fgetc(stream)) != EOF && c != '\n') {
    if (len + 1 >= *n) {
      *n *= 2;
      buffer = realloc(buffer, *n);
      if (buffer == NULL) return -1;
      *lineptr = buffer;
  }
  buffer[len++] = c;
  }

  if (c == EOF && len == 0) return -1;

  buffer[len] = '\0';
  return len;
}

int main() {
  char *line = NULL;
  size_t len = 0;

  printf("Enter a line of text:\n");
  if (my_getline(&line, &len, stdin) != -1) {
      printf("You entered: %s", line);
  }

  free(line);
  return 0;
}
