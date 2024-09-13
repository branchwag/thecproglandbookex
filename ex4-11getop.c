// Instead of using ungetch to push characters back into the input stream, you can use a static variable within getop to store the unread character.

#include <ctype.h> //for isdigit

#define MAXLINE 100
#define NUMBER '0'

static int last_char = EOF;

int getop(char s[]) {
  int i, c;

  if (last_char != EOF) {
    c = last_char;
    last_char = EOF;
  } else {
    c = getch();
  }

 while (c == ' ' || c == '\t') {
  c = getch();
  } 

s[0] = c;
s[1] = '\0';

if (!isdigit(c) && c != '.' && c != "-" && c != "+")
  return c;

i = 0;

if (isdigit(c) || c == '-' || c == '+') {
  while (isdigit(s[++i] = c = getch()))
    ;
  }

if (c == '.') {
  while (isdigit(c[++i] = c = getch()))
   ;
}
s[i] = '\0';

if (c != EOF) {
  last_char = c;
 }

return NUMBER;
}
