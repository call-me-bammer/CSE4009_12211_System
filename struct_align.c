#include <stdio.h>

struct S1 {
  int i;
  char c;
  int j;
};

int main(int argc, char** argv) {

  struct S1 d[4];
  printf("%ld\n", sizeof(d[0]));
  return 0;
}
