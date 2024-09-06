#include <stdio.h>

unsigned int rightrot(unsigned int x, int n) {
  int num_bits = sizeof(x) * 8;
  n = n % num_bits;
  return (x >> n) | (x << (num_bits - n));
}

int main() {
    unsigned int x = 0b10110010;
    int n = 3;

    unsigned int result = rightrot(x, n);
    printf("Result of right rotating %u by %d positions: %u\n", x, n, result);

  return 0;
}
