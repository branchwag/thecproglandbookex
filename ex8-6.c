//write calloc
//calloc(n,size) returns a pointer to n objects of size size, w/ storage inited to 0

//allocate mem
//init mem to 0
//return pointer

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *calloc(size_t n, size_t size) {
  void *ptr = malloc(n * size);
  if (ptr == NULL) { 
    return NULL;
  }

  memset(ptr, 0, n * size); //destination, value, size. Init mem to 0.

  return ptr;
}

int main() {
  size_t n = 5;
  size_t size = sizeof(int);

  int *arr = (int *)calloc(n, size);

  if (arr == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  for (size_t i = 0; i < n; ++i) {
       printf("arr[%zu] = %d\n", i, arr[i]);
  }

  free(arr);

  return 0;
}



