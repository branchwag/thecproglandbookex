#include <stdio.h>
#include <string.h>

//Write a version of itoa (integer to ASCII) that accepts three arguments instead of two. The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough.

void itoa(int n, char s[], int width) {
  int i = 0, sign;

  if ((sign = n) < 0) {
    n = -n;
  }

  do {
      s[i++] = n % 10 + '0';
      } while ((n /= 10) > 0);
  
  if (sign  < 0) {
        s[i++] = '-';
   }

  s[i] = '\0';

  for (int j = 0; j < i / 2; j++) {
       char temp = s[j];
       s[j] = s[i - j - 1];
       s[i - j - 1] = temp;
  }

  int len = strlen(s);
  if (len < width) {
    for (int j = len; j >= 0; j--) {
         s[j + (width - len)] = s[j];
    }
    for (int j = 0; j < width -len; j++) {
         s[j] = ' ';
    }
  }
}

int main() {
  char buffer[50];
    itoa(123, buffer, 10);
    printf("'%s'\n", buffer);  // Output will be '        123'
    itoa(-4567, buffer, 10);
    printf("'%s'\n", buffer);  // Output will be '     -4567'
    itoa(89, buffer, 5);
    printf("'%s'\n", buffer);  // Output will be '   89'
  return 0;
}
