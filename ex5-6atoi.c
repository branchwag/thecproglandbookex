//atoi converts a string to an integer
#include <stdio.h>

int atoi(const char *str) {
  int sign = 1;
  int num = 0;
  
  if(*str == '-') {
    sign = -1;
    str++;
  }

  while(*str >= '0' && *str <= '9') {
    num = num * 10 + (*str - '0');
    str++;
  }

  return sign * num;
}

int main() {
  char numStr[] = "-12345";
  printf("String '%s' as integer is %d\n", numStr, atoi(numStr));
  return 0;
}
