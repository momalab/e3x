#include <stdio.h>
#include "src/unumber/unumberg.h"

int main()
{
	Unumber a (3), b (8), c;

	c = a * b;
	printf("%llu\n", c.to_ull());

	return 0;
}

