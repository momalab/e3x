#include <iostream>
#include "../../src/e3extensions/secureint.h"

using namespace std;

string libgDir = "./libg.so";
string gFunctionName = "libg";

int main()
{
	Cryptosystem cs(__PQ(58271)(49169)(5)(18), __BETA, __2TOBETA, __HALFTABLE, __ENC0, __ENC1, libgDir, gFunctionName);

	SecureInt a (__E(0x4d),cs);
	SecureInt b (__E(0x61),cs);
	SecureInt c (__E(0x6c),cs);
	SecureInt d (__E(0x61),cs);
	SecureInt e (__E(0x6b),cs);
	SecureInt f (__E(0x61),cs);

	cout << a.str() << " " << b.str() << " " << c.str() << " " << d.str() << " " << e.str() << " " << f.str() << "\n";

/*
	SecureInt a[3][3] = { {SecureInt(1,cs),SecureInt(2,cs),SecureInt(3,cs)}, {SecureInt(2,cs),SecureInt(3,cs),SecureInt(4,cs)}, {SecureInt(3,cs),SecureInt(4,cs),SecureInt(5,cs)} };
	SecureInt b[3][3] = { {SecureInt(1,cs),SecureInt(2,cs),SecureInt(3,cs)}, {SecureInt(2,cs),SecureInt(3,cs),SecureInt(4,cs)}, {SecureInt(3,cs),SecureInt(4,cs),SecureInt(5,cs)} };
	SecureInt c[3][3];
	SecureInt zero (0,cs);
*/
/*
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			c[i][j] = zero;
			for (int k = 0; k < 3; k++) c[i][j] += a[i][k] * b[k][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) cout << c[i][j].str() << " ";
		cout << "\n";
	}
*/

	return 0;
}

