#include <stdio.h>

unsigned int invert(unsigned int x, unsigned int p, unsigned int n) {
  unsigned int mask = (1U << n) - 1;
  mask <<= p;
  return x ^ mask;
}

int main() {
  unsigned int x = 0b11001100;
  unsigned int p = 2;
  unsigned int n = 4;

  unsigned int result = invert(x, p, n);
  printf("Result: %u\n", result);
  printf("Result (binary): 0b");
  for (int i = sizeof(result) * 8 - 1; i >= 0; i--) { 
       printf("%d", (result >> i) & 1); 
  }
  printf("\n");
  return 0;
}


