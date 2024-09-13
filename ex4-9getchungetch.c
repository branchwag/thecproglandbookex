#include <stdio.h>

static int pushback = EOF;

int getch(void) {
  int c;
  if (pushback != EOF) {
    c = pushback;
    pushback = EOF;
  } else {
    c = getchar();
  }
  return c;
}

void ungetch(int c) {
  if (pushback != EOF) {
    if (c == EOF) {
        printf("ungetch: pushback area already occupied\n");
    } else {
        pushback = c;
    }
  } else {
        pushback = c;
    }
}
