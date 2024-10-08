//malloc accepts a size request without checking plausibility
//free believes that the block it is asked to free contaisn a valid size field
//improve both with error checking

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

void error(const char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

void *malloc_checked(size_t n, size_t size) {
  if (size == 0 || n == 0) {
    error("malloc_checked: size or n cannot be zero");
  }

  if (n > SIZE_MAX / size) {
    error("malloc_checked: memory allocation request overflow");
  }

  void *ptr = malloc(n * size);
  if (ptr == NULL) {
    error("malloc_checked: memory allocation failed");
  }

  return ptr;
}

void free_checked(void *ptr) {
  if (ptr == NULL) {
    error("free_checked: attempted to free a NULL pointer");
  }

  free(ptr);
}

int main() {
  size_t n = 10;
  size_t size = sizeof(int);

  int *arr = (int *)malloc_checked(n, size);

  for (size_t i = 0; i < n; ++i) {
      arr[i] = i * 10;
  }

  for (size_t i = 0; i < n; ++i) {
       printf("arr[%zu] = %d\n", i, arr[i]);
  }

  free_checked(arr);

  return 0;
}

