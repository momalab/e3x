#include <iostream>
#include "../../src/e3extensions/secureint.h"

#define IT 10
#define MOD (IT / 10)

using namespace std;

string libgDir = "./libg.so";
string gFunctionName = "libg";

int main()
{
	Cryptosystem cs("8391067594105520693",8,{"10192053919619517975363985245347619613","41752951296378218322740673092739432785","16211246861228892047407554302003325362","23575445693372558299108255688540992237","13459052381271437465223441767490490193","43598149771205848292813297387350293377","48527268168162526810035578564018720522","67349295572984366883230219900374804119","12969279240536693003428913904435292266"}, libgDir, gFunctionName,"10526905565375083675140114074209533519");
	SecureInt a ("22311449736424396905900363739960186281",cs);
	SecureInt b ("2825881012887429831045838662379198622",cs);
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

