//handle cases where a + or - not followed by a digit. Push char back onto input stream rather than treating it as a zero.
//getint reads an integer from input

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);

int getint(int *pn) {
  int c, sign;

  while (isspace(c = getch()))
    ;

  if (c == '+' || c == '-') {
    sign = (c == '-') ? -1: 1;
    c = getch();

    if (!isdigit(c)) {
      ungetch(c);
    if (c == '+') c = '0';
    else if (c == '-') c = '0';
    else ungetch(c);
    *pn = 0;
    return 0;
  }
  } else {
      sign = 1;
      ungetch(c);
  }

  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF) ungetch(c);
  return (c == EOF && *pn == 0) ? EOF : 1;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
      printf("ungetch: too many characters\n");
  else 
      buf[bufp++] = c;
}

int main(void) {
  int n;
  int result;

    printf("Enter integers (end with Ctrl+D or Ctrl+Z):\n");
    while ((result = getint(&n)) != EOF) {
        if (result == 0) {
            printf("Invalid input or sign without following digit\n");
        } else {
            printf("Read integer: %d\n", n);
        }
    }

    return 0;
}
