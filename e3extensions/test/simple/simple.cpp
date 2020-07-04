#include <iostream>
#include <fstream>
#include "../../src/e3extensions/secureint.h"

using namespace std;

string libgDir = "./libg.so";
string gFunctionName = "libg";

int main()
{
	cout << "Creating Cryptosystem\n";
	Cryptosystem cs(__PQ()()()()__, __BETA__, __2TOBETA__, __ENC0__, __ENC1__, libgDir, gFunctionName);
	cout << "Instantiating SecureInts\n";
	SecureInt a(__N(1)__,cs), b(__N(15)__,cs), c(__N(10)__,cs), d(__N(7)__,cs);
	cout << "Performing mathematical equation (it may take a while)\n";
	SecureInt r = a+b*c-d;
	cout << "Writing output file\n";
	ofstream out;
	out.open("output.txt", ofstream::out);
	out << r.str();
	out.close();

	return 0;
}

