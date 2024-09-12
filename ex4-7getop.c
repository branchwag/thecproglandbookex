#include <stdio.h>
#include <ctype.h>
#include <string.h>

//cc ex4-5main.c ex4-5getchungetch.c ex4-5getop.c ex4-5pushpop.c 

#define NUMBER '0'
#define MODULO '%'
#define PRINT 'p'
#define DUPLICATE 'd'
#define SWAP 's'
#define CLEAR 'c'
#define FUNC 'f'
#define VAR 'v'

int getch(void);
void ungetch(int);

int getop(char s[]) {
  int i, c;
  char func[10];

  //skip whitespace
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;

  if (c == '=') {
    s[1] = getch();
    s[2] = '\0';
    return VAR;
  }
  if (isupper(c)) {
    s[0] = c;
    s[1] = '\0';
    return VAR;
  }

  if (isalpha(c)) {
    i = 0;
    func[i++] = c;
    while (isalpha(c = getch()))
      func[i++] = c;
      func[i] = '\0';
      ungetch(c);
    if (strcmp(func, "sin") == 0 || strcmp(func, "exp") == 0 || strcmp(func, "pow") == 0)
      return FUNC;
    else 
      return func[0];
  }

  if (c == PRINT || c == DUPLICATE || c == SWAP || c == CLEAR) {
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
