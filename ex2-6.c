#include <stdio.h>

unsigned int setbits (unsigned int x, int p, int n, unsigned int y) {
  unsigned int y_mask = (1U << n) - 1;
  unsigned int y_bits = y & y_mask;
  
  y_bits <<= (p - n + 1);

  unsigned int clear_mask = ~(y_mask << (p - n + 1));

  return (x & clear_mask) | y_bits;
}

int main () {
  unsigned int x = 0xFFFF;
  int p = 7;
  int n = 3;
  unsigned int y = 0x3;

  unsigned int result = setbits(x, p, n, y);
  printf("Result: 0x%X\n", result);

  return 0;
}
