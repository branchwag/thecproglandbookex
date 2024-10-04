//hand roll isupper to save space or time
//space
#include <stdio.h>

//fewer comparisons for space efficiency
int isupper_space(char c) {
  return c >= 'A' && c <= 'Z';
}

int main () {
 char test_char = 'A';
 printf("issupper_space('%c') = %d\n", test_char, isupper_space(test_char));
  return 0;
}
