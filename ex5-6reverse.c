//reverses a string

#include <stdio.h>

void reverse(char *str) {
  char *end = str;
  char temp;

  if (str) {
    while (*end) {
        end++;
    }
    end--;

    while (str < end) {
      temp = *str;
      *str++ = *end;
      *end-- = temp;
    }
  }
}

int main() {
  char str[] = "hello";
  reverse(str);
  printf("Reversed string: %s\n", str);
  return 0;
}
