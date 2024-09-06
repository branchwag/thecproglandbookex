#include <stdio.h>
#include <stdbool.h>

bool is_in_string(const char s[], char c) {
  int i = 0;
  while (s[i] != '\0') {
    if (s[i] == c) {
      return true;
    }
    i++;
  }
  return false;
}

void squeeze(char s1[], const char s2[]) { 
  int i, j;
  for (i = j = 0; s1[i] != '\0'; i++) {
       if (!is_in_string(s2, s1[i])) {
          s1[j++] = s1[i];
        }
      }
      s1[j] = '\0';
}

int main () {
  char s1[] = "hello, world";
  char s2[] = "ol";

  printf("original string: %s\n", s1);
  printf("Characters to remove: %s\n", s2);
  squeeze(s1,s2);
  
  printf("Modified string: %s\n", s1);

  return 0;
}
