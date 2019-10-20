#include <stdio.h>

long absdiff_j(long x, long y) {

        long result;
        int ntest = (x <= y);

        if (ntest)
                goto Else;
        result = x-y;
        	goto Done;

Else:
        return = y-x;
Done:
        return result;
}

int main() {

	long x = 10, y = 7;
	long z = absdiff_j(10, 7);
	printf("%ld\n", z);
	return 0;
}
