//converts int to string

#include <stdio.h>

char *itoa(int num, char *str, int base) {
  char *ptr = str;
  char *ptr1 = str;
  char tmp;
  int i;

  if (num < 0 && base == 10) {
    *ptr++ = '-';
    num = -num;
  }

  do {
    i = num % base;
    *ptr++ = (i > 9) ? (i - 10) + 'a' : i + '0';
    num /= base;
  } while (num > 0);

  *ptr-- = '\0';

  while (ptr1 < ptr) {
    tmp = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp;
  }

  return str;
}

int main() {
  char buffer[20];
  int num = 1234;
  printf("Integer %d as string is %s\n", num, itoa(num, buffer, 10));
  return 0;
}
