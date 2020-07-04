#include <iostream>
#include "../../src/e3extensions/secureint.h"

#define IT 10
#define MOD (IT / 10)

using namespace std;

string libgDir = "./libg.so";
string gFunctionName = "libg";

int main()
{
	Cryptosystem cs("34189",8,{"186005528","85417041","108559584","122555535","605171812","831201734","489751043","1061709281","271623197"}, libgDir, gFunctionName,"227288473");
	SecureInt a ("55789079",cs);
	SecureInt b ("790588293",cs);
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

