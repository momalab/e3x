#include <iostream>
#include "../../src/e3extensions/secureint.h"

#define MESSAGE "Enter a text (ctrl c to exit): "

using namespace std;

string libgDir = "./libg.so";
string gFunctionName = "libg";

int main()
{
	Cryptosystem cs(__PQ()()()(), __BETA, __HALFTABLE, libgDir, gFunctionName, __GEN);
	SecureInt a;
	string text;
	char c;

	while (true) {
		cout << "\n" << MESSAGE;
		cin >> text;

		for (unsigned i = 0; i < text.length(); i++) {
			c = text.at(i);
			a = SecureInt(c,cs);
			cout << a.str(); 
		}
	}

	return 0;
}

