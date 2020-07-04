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
	Cryptosystem cs("13647083806282194253","16","125288032111545322912292519101500555978","148922171416570582644641245385173685935","88562429946875480076437148089833743090", libgDir, gFunctionName);
	e = PAPI_get_real_cyc();
	cout << "Cryptosystem cs: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	SecureInt a("110693799722707411750196810838976487548",cs);
	e = PAPI_get_real_cyc();
	cout << "SecureInt a: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	SecureInt b("3215022537006813162303397697285371362",cs);
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

