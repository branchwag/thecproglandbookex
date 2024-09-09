#include <stdio.h>
#include <time.h>

#define SIZE 1000000

int binsearch_old(int x, int v[], int n) {
  int low, high, mid;
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else 
      return mid;
    }
    return -1;
}

int binsearch_new(int x, int v[], int n) {
  int low, high, mid;
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (x == v[mid])
      return mid;
    else if (x < v[mid])
      high = mid - 1;
    else
      low = mid + 1;
   }
   return -1;
}

int main() {
  int v[SIZE];
  for (int i = 0; i < SIZE; i++) {
       v[i] - i;
  }

  int target = SIZE / 2;

  clock_t start = clock();
  binsearch_old(target, v, SIZE);
  clock_t end = clock();
  double time_old = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Old version took %f seconds.\n", time_old);

  start = clock();
  binsearch_new(target, v, SIZE);
  end = clock();
  double time_new = (double)(end - start) / CLOCKS_PER_SEC;
  printf("New version took %f seconds.\n", time_new);

  return 0;
}
