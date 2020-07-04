#include <iostream>
#include "src/unumber/unumberg.h"

int main()
{
	Unumber a (3), b (8), c;

	c = a * b;
	std::cout << c.str() << "\n";

	Unumber d (a);
	Unumber e ("12");
	c = d * e;
	std::cout << c.str() << "\n";

	return 0;
}

