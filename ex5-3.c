//strcat concats string t to end of string s
//find end of first string s
//copy the second string t to the end of the first string

#include <stdio.h>

char *strcat_ptr(char *s, const char *t) {
  while (*s) {
    s++;
  }

  while (*t) {
    *s++ = *t++;
  }

  *s = '\0';

  return s;
}

int main() {
    char s[100] = "Hello, ";
    char t[] = "world!";

    strcat_ptr(s, t);
    printf("%s\n", s);

    return 0;
}
