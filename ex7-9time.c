//hand roll isupper to save space or time
//time

#include <stdio.h>

//avoid doing compare each time func is called
//use array - init lookup table for 256 asci chars and prefill lookup with uppers
//reduces time but uses more mem
int isupper_time(char c) {
  static int lookup[256] = {0};
  if (lookup['A'] == 0) {
    for (int i = 'A'; i <= 'Z'; i++) {
         lookup[i] = 1;
    }
  }
  return lookup[(unsigned char) c];
}

int main() {
  char test_char = 'A';
  printf("isupper_time('%c') = %d\n", test_char, isupper_time(test_char));
  return 0;
}

