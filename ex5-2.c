#include <stdio.h>
#include <math.h> //for pow
#include <ctype.h>
#include <stdlib.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);

int getfloat(float *pn) {
  int c, sign;
  float power, exponent; 

  while (isspace(c = getch()))
    ;

    if (c == '+' || c == '-') {
      sign = (c == '-') ? -1 : 1;
      c = getch();
    } else {
        sign = 1;
    }

    for (*pn = 0.0; isdigit(c); c = getch())
      *pn = 10.0 * *pn + (c - '0');

    if (c == '.') {
      c = getch();
      for (power = 1.0; isdigit(c); c = getch()) {
          *pn = 10.0 * *pn + (c - '0');
          power *= 10.0;
      }
      *pn /= power;
    }


    if (c == 'e' || c == 'E') {
      int exp_sign = 1;
      c = getch();
      if (c == '+' || c == '-') {
        exp_sign = (c == '-') ? -1 : 1;
        c = getch();
      } 
      for (exponent = 0.0; isdigit(c); c = getch())
          exponent = 10.0 * exponent + (c - '0');
      *pn *= (exp_sign == 1) ? pow(10.0, exponent) : pow(10.0, -exponent);
  }

  *pn *= sign;
  if (c != EOF) ungetch(c);
  
  return (c == EOF && *pn == 0.0) ? EOF: 1;
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
  float x;
  int result;

    printf("Enter floating-point numbers (end with Ctrl+D or Ctrl+Z for EOF indication):\n");
    while ((result = getfloat(&x)) != EOF) {
        if (result == 0) {
            printf("Invalid input\n");
        } else {
            printf("Read floating-point number: %f\n", x);
        }
    }

    return 0;
} 
