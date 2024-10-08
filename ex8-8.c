//write bfree(p.n)
//free any block p pf n chars into the free list maintained by malloc and free
//user can add static or external array to the free list at any time
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct free_block {
  size_t size;
  struct free_block *next;
};

static struct free_block *free_list = NULL;

void bfree(void *p, size_t n) {
  if (p == NULL) {
    return;
  }

  struct free_block *block = (struct free_block *)p;

  block->size = n;

  block->next = free_list;
  free_list = block;
}

void print_free_list() {
  struct free_block *curr = free_list;
  while (curr != NULL) {
    printf("Block size: %zu\n", curr->size);
    curr = curr->next;
  }
}

int main() {
  size_t block_size = 100;
  char *p = (char *)malloc(block_size);
  printf("Block allocated at address: %p\n", p);
  bfree(p, block_size);
  printf("Free list after bfree:\n");
  print_free_list();
  free(p);
  return 0;
}
