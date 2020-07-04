#include <iostream>
#include <fstream>
#include "../../src/e3extensions/secureint.h"

using namespace std;

string libgDir = "./libg.so";
string gFunctionName = "libg";

int main()
{
	cout << "Creating Cryptosystem\n";
	Cryptosystem cs("106037","14","489906008","10546378165","2718129991", libgDir, gFunctionName);
	cout << "Instantiating SecureInts\n";
	SecureInt a("7835062305",cs), b("10023955253",cs), c("9114366194",cs), d("5036267407",cs);
	cout << "Performing mathematical equation (it may take a while)\n";
	SecureInt r = a+b*c-d;
	cout << "Writing output file\n";
	ofstream out;
	out.open("output.txt", ofstream::out);
	out << r.str();
	out.close();

	return 0;
}

