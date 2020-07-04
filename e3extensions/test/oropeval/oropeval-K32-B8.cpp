#include <iostream>
#include "../../src/e3extensions/secureint.h"

#define IT 10
#define MOD (IT / 10)

using namespace std;

string libgDir = "./libg.so";
string gFunctionName = "libg";

int main()
{
	Cryptosystem cs("1174758241",8,{"829620066186068028","467819585157443354","1138311664203757676","409830433182141368","1365016720958258165","249295765421750394","768119667757654522","1221191537731868421","287979884607126973"}, libgDir, gFunctionName,"1043773534731125834");
	SecureInt a ("501319365340231065",cs);
	SecureInt b ("700748938373477418",cs);
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

