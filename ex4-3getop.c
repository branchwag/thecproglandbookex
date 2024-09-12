#include <stdio.h>
#include <ctype.h>

//cc ex4-3main.c ex4-3getchungetch.c ex4-3getop.c ex4-3pushpop.c 

#define NUMBER '0'
#define MODULO '%'

int getch(void);
void ungetch(int);

int getop(char s[]) {
  int i, c;
  //skip whitespace
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  //check for neg nums
  if (c == '-') {
    if (isdigit(c = getch())) {
      s[0] = '-';
    } else {
      ungetch(c);
      return '-';
    }
  } else {
    s[1] = '\0';
  }

  if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '\n') {
    return c;
  }

  //check if num or decimal num
  if (!isdigit(c) && c != '.')
    return c;
  
  i = 0;
  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}
