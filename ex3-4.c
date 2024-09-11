#include <stdio.h>
#include <string.h>
#include <limits.h> //for INT_MIN
//smallest neg number is -2147483648
//2147483648 out of positive range for 32-bit integer

void reverse(char s[]) {
  int i, j; 
  char c;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
       c = s[i];
       s[i] = s[j];
       s[j] = c;
  }
}

void itoa(int n, char s[]) {
  int i, sign;

  if (n == INT_MIN) {
    snprintf(s, 12, "%d", n);
    return;
  }

  if ((sign = n) < 0) {
    n = -n;
  }

  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) {
    s[i++] = '-';
  }

  s[i] = '\0';
  reverse(s);
}

int main() {
  char str[50];
  int n = -2147483648;
  itoa(n, str);
  printf("itoa(%d) = %s\n", n, str);
  return 0;
}
