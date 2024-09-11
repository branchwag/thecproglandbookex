#include <stdio.h>
#include <ctype.h>

void expand(const char s1[], char s2[]) {
  int i, j;
  char c;

  for (i = 0, j = 0; s1[i] != '\0'; i++) {
       if (s1[i] == '-' && i > 0 && s1[i+1] != '\0') {
       if (isalpha(s1[i-1]) && isalpha(s1[i+1])) {
         char start = s1[i-1];
         char end = s1[i+1];
         if (start > end) {
           char temp = start;
           start = end;
           end = temp;
       }
       for (c = start + 1; c < end; c++) {
         s2[j++] = c;
       }
       i++;
      } else if (isdigit(s1[i-1]) && isdigit(s1[i+1])) {
         char start = s1[i-1];
         char end = s1[i+1];
         if (start > end) {
           char temp = start;
           start = end;
           end = temp;
       }
       for (c = start + 1; c < end; c++) {
         s2[j++] = c;
       }
         i++;
       } else {
         s2[j++] = s1[i];
       }
      } else {
       s2[j++] = s1[i];
       }
      }
      s2[j] = '\0';
}

int main() {
  char s1[] = "a-z0-9-";
  char s2[100];
  expand(s1, s2);
  printf("Expanded: %s\n", s2);
  return 0;
}
