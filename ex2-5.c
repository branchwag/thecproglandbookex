#include <stdio.h>

int any(const char s1[], const char s2[]) {
  int i, j;

  for (i = 0; s1[i] != '\0'; i++) {
       for (j = 0; s2[j] != '\0'; j++) {
          if (s1[i] == s2[j]) {
            return i;
           }
       }
    }
    
    return -1;
}

int main() {
  char s1[] = "hello, world";
  char s2[] = "aeiou";

  int index = any(s1, s2);

  if (index != -1) {
     printf("First occurence of any character from s2 in s1 is at index %d.\n", index);
   } else {
     printf("No characters from s2 are found in s1.\n");
   }

  return 0;
}
