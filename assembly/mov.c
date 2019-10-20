#include <stdio.h>
#include <stdlib.h>

void swap(long* xp, long* yp) {

  long tmp = *xp;
  *xp = *yp;
  *yp = tmp;
}

int main() {

  long a = 4, b = 5;
  swap(&a, &b);
  return 0;
}
