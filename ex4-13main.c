//Write a recursive version of the function reverse(s), which reverses the string s in place.
#include <stdio.h>
#include <string.h>

void reverse(char s[], int start, int end) {
    if (start >= end) {
      return;
  }

  char temp = s[start];
  s[start] = s[end];
  s[end] = temp;

  reverse(s, start + 1, end - 1);
}

int main() {
  char s[] = "Hello, World!";
  int len = strlen(s);

  reverse(s, 0, len - 1);

  printf("Reversed string: %s\n", s);
  return 0;
}
