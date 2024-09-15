//strncpy(s, t, n) copies up to n chars from string t to string s
//strncar(s, t, n) appends up to n chars from string t to end of string s
//strncmp(s, t, n) compares at most n chars of string s with string t


#include <stdio.h>
#include <stddef.h> // for null

char *my_strncpy(char *s, const char *t, size_t n) {
  size_t i;
  for (i = 0; i < n && t[i] != '\0'; i++) {
       s[i] = t[i];
  }

  for (; i < n; i++) {
       s[i] = '\0';
  }
  return s;
}

char *my_strncat(char *s, const char *t, size_t n) {
  char *p = s;

  while (*p != '\0') {
    p++;
  }

  while (n-- > 0 && *t != '\0') {
    *p++ = *t++;
  }

  *p = '\0';

  return s;
}

int my_strncmp(const char *s, const char *t, size_t n) {
  while (n-- > 0 && *s != '\0' && *t != '\0') {
    if(*s != *t) {
      return (unsigned char)*s - (unsigned char)*t;
    }
    s++;
    t++;
  }

  if (n == (size_t)-1) {
    return 0;
  }
  return (unsigned char)*s - (unsigned char)*t;
}


int main() {
  char s1[20] = "Hello";
  char s2[20] = "World";
  char s3[20];

  my_strncpy(s3, s1, 3);
  printf("strncpy: %s\n", s3); // Hel

  my_strncat(s1, s2, 3);
  printf("strncat: %s\n", s1); //HelloWor

  int result = my_strncmp(s1, s2, 3);
  printf("strncmp: %d\n", result);

  return 0;
}

