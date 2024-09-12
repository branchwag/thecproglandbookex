#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXDIGITS 64

/*Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s.*/
void reverse(char s[]) {
  int i, j;
  char c;
  int len = strlen(s);
  for (i = 0, j = len - 1; i < j; i++, j--) {
       c = s[i];
       s[i] = s[j];
       s[j] = c;
  }
}

void itob(int n, char s[], int b) {
  //convert n into base b char representation in string s
  int i = 0;
  int sign;

  if (b < 2 || b > 36) {
    s[0] = '\0';
    return;
  }

  if (n == 0) {
    s[i++] = '0';
    s[i] = '\0';
    return;
  }

  if (n < 0) {
    sign = -1;
    n = -n;
  } else {
    sign = 1;
  }

  while (n > 0) {
    int digit = n % b;
    if (digit < 10) {
      s[i++] = digit + '0';
    } else {
        s[i++] = digit - 10 + 'a';
    }
    n /= b;
  }

  if (sign < 0) {
    s[i++] = '-';
  }

  s[i] = '\0';
  reverse(s);
}

int main() {
  char str[MAXDIGITS];
  int n = 255;

  itob(n, str, 16);
  printf("itob(%d, s, 16) = %s\n", n, str);

  itob(n, str, 2);
  printf("itob(%d, s, 2) = %s\n", n, str);

  itob(n, str, 10);
  printf("itob(%d, s, 10) = %s\n", n, str);

  return 0;
}
