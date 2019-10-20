#include <stdio.h>

/* Plus, stack canary is called! */

int main() {

	int* p;
	int x[10] = { 7 };

	p = &x[5];

	return 0;
}
