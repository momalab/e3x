#include <iostream>
#include "../../src/e3extensions/secureint.h"

#define IT 10
#define MOD (IT / 10)

using namespace std;

string libgDir = "./libg.so";
string gFunctionName = "libg";

int main()
{
	Cryptosystem cs(__PQ()()()(), __BETA, __HALFTABLE, libgDir, gFunctionName, __GEN);
	SecureInt a (__E(7),cs);
	SecureInt b (__E(1),cs);
	SecureInt c;
	unsigned bi = 1;

	for (int i = 0; i < IT; i++)
	{
		//a += b;
		//a -= b;
		a *= b;
		//a <<= b;
		//a <<= bi;
		//a >>= b;
		//a >>= bi;
		//a = SecureInt(bi,cs);
		//a = SecureInt::G(a,b);
		//a = a == b;
		//a = a != b;
		//a = a > b;
		//a = a < b;
		//a = a >= b;
		//a = a <= b;
		
		if ((i % MOD) == 0) cout << i << "\n";
		//cout << i << "\n";
	}
	cout << a.str() << "\n";

	return 0;
}

