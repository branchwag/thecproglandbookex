#include <stdio.h>

int getch(void);
void ungetch(int);

int main() {
  int c;

  printf("Enter a character: ");
  c = getch();
  printf("Read character: %c\n", c);

  ungetch(c == EOF ? EOF : c);

  c = getch();
  if (c == EOF) {
    printf("Read EOF again\n");
  } else {
    printf("Read character again: %c\n", c);
  }

  return 0;
}
