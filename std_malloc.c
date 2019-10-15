#include <stdio.h>
#include <stdlib.h>


void* mm_malloc(size_t size);
void mm_free(void* bp);
void str_malloc(int n);




int main(int argc, char ** argv) {

  str_malloc(10);
  return 0;
}


void* mm_malloc(size_t size) {

  /* Allocate an even number of words
  to maintain double-word alignment */
  size_t s = (size % 2) ? size + 1 : size;

}

void mm_free(void* bp) {

  *bp = *bp & -2;
  void* next = bp + *bp;

  if ((*next & 1) == 0)
    *bp = *bp + *next;
}


void str_malloc(int n) {

  int i;
  int* p;

  /* Allocate a block of n ints */
  p = (int*)malloc(n * sizeof(int));
  if (p == NULL) {
    perror("std_malloc");
    exit(0);
  }

  /* Initialize allocated block */
  for (i = 0; i < n; i++) {
    p[i] = i;
    printf("%d ", p[i]);
  }
  printf("\n");

  /* Return allocated block to the heap */
  free(p);
}
