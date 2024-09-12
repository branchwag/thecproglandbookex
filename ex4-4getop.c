#include <stdio.h>
#include <ctype.h>

//cc ex4-4main.c ex4-4getchungetch.c ex4-4getop.c ex4-4pushpop.c 

#define NUMBER '0'
#define MODULO '%'
#define PRINT 'p'
#define DUPLICATE 'd'
#define SWAP 's'
#define CLEAR 'c'

int getch(void);
void ungetch(int);

int getop(char s[]) {
  int i, c;
  //skip whitespace
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;

  if (c == PRINT || c == DUPLICATE || c == SWAP || c == CLEAR) {
    s[1] = '\0';
    return c;
  }

    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '\n') {
    return c;
  }


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
