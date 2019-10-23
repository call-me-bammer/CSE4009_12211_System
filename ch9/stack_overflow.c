#include <stdio.h>

typedef struct {
    int a[2];
    double d;
} struct_t;

double fun(int i);

int recurse(int x);

void echo(void);

int main(int argc, char** argv) {

    int i;

    //recurse(48);
    for (i = 0; i < 10; i++)
        printf("fun(%d) -> %f\n", i, fun(i));

    return 0;
}


double fun(int i) {
    volatile struct_t s;
    s.d = 3.14;
    s.a[i] = 1073741824; /* Possibly out of bounds */
    return s.d;
}

int recurse(int x) {

    // 1 and 17 zeros...
    // == 10 0000 0000 0000 0000
    // == 128 KiB
    int a[2 << 15];
    printf("x = %d. a at %p\n", x, a);

    a[0] = (2 << 13) - 1;
    a[a[0]] = x - 1;

    if (a[a[0]] == 0)
        return -1;
    return recurse(a[a[0]]) - 1;
}

void echo(void) {

    char buf[4];
    gets(buf);
    puts(buf);
}