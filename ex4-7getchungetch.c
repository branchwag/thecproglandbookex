#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

char buf[BUFSIZE]; //buffer to hold chars
int bufp = 0; // next free pos in buf

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n"); 
  else
    buf[bufp++] = c;
}

void ungets(char s[]) {
  int len = strlen(s);
  while (len > 0) {
    ungetch(s[--len]);
  }
}
