#include <iostream>
#include "../../src/e3extensions/secureint.h"
#include <papi.h>

using namespace std;

string libgDir = "./libg.so";
string gFunctionName = "libg";

int main()
{
	long long s, e;

	s = PAPI_get_real_cyc();
	for (int i = 0; i < 1000000; i++) asm volatile("nop");
	e = PAPI_get_real_cyc();
	cout << "For loop: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	Cryptosystem cs(__PQ()()()(), __BETA, __2TOBETA, __HALFTABLE, __ENC0, __ENC1, libgDir, gFunctionName);
	e = PAPI_get_real_cyc();
	cout << "Cryptosystem cs: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	SecureInt a(__E(49),cs);
	e = PAPI_get_real_cyc();
	cout << "SecureInt a: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	SecureInt b(__E(12),cs);
	e = PAPI_get_real_cyc();
	cout << "SecureInt b: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	SecureInt c;
	e = PAPI_get_real_cyc();
	cout << "SecureInt c: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	c = a + b;
	e = PAPI_get_real_cyc();
	cout << "c = a + b: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	c = a * b;
	e = PAPI_get_real_cyc();
	cout << "c = a * b: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	c = SecureInt::G(a,b);
	e = PAPI_get_real_cyc();
	cout << "c = G(a,b): " << (e-s) << " cycles\n";	

	return 0;
}

