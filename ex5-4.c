//write function strend(s, t) that checks if string t occurs at end of string s
// return 1 if string t is found at end of s, 0 otherwise
#include <stdio.h>
#include <string.h>

int strend(const char *s, const char *t) {
  size_t len_s = strlen(s);
  size_t len_t = strlen(t);

  if (len_t > len_s) {
    return 0;
  }

  s += len_s - len_t;
  return strcmp(s, t) == 0;
}

int main() {
  const char *s = "Hello, world!";
  const char *t1 = "world!";
  const char *t2 = "Hello";

  printf("Does '%s' end with '%s'? %d\n", s, t1, strend(s, t1));
  printf("Does '%s' end with '%s'? %d\n", s, t2, strend(s, t2));

  return 0;
}
