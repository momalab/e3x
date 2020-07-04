/*******************************************
*  DDD   EEEE  BBB   U  U   GG       DEBUG *
*  D  D  E     B  B  U  U  G               *
*  D  D  EEE   BBB   U  U  G GG            *
*  D  D  E     B  B  U  U  G  G            *
*  DDD   EEEE  BBB    UU    GG   2016-2017 *
********************************************/

//#define STATIC_LIBG
//#include "../../src/libg/libg.cpp"

#ifndef IOSTREAM_INCLUDED
	#define IOSTREAM_INCLUDED
	#include <iostream>
#endif

#ifndef SECUREINT_INCLUDED
	#define SECUREINT_INCLUDED
	#include "../../src/e3extensions/secureint.h"
#endif

#ifndef SENSITIVE_INFORMATION_INCLUDED
	#define SENSITIVE_INFORMATION_INCLUDED
	#include "../../src/preprocessor/sensitive_information.h"
#endif

#ifndef STDIO_INCLUDED
	#define STDIO_INCLUDED
	#include <stdio.h>
#endif

using namespace std;

string libgDir = "";

void printPair(const Unumber, const Unumber);

/*
 * P and Q must be different prime numbers
 * K and RND must not be multiple of P or Q
 */

int main()
{
	/* Using SensitiveInformation to test SecureInt */

	//SensitiveInformation (p,q,k,rnd);
	//SensitiveInformation si ("104947","105613","3","2");
	cout << "Sensitive Information\n";
	SensitiveInformation si ("13","11","3","2");
	cout << "Unumber\n";
	Unumber udecA(11), udecB(3);

	cout << "Encrypting...\n";

	Unumber uencA = si.encrypt(udecA);
	Unumber uencB = si.encrypt(udecB);

	cout << "Inputs:\n";

	printPair(udecA, uencA);
	printPair(udecB, uencB);

        cout << "g: " << si.access_g().str() << "\n";
        cout << "Nm1: " << si.access_Nm1().str() << "\n";
        cout << "p1Nk1N: " << si.access_p1Nk1N().str() << "\n";
        cout << "phi: " << si.access_phi().str() << "\n";
        cout << "fkf: " << si.fkf().str() << "\n";
        cout << "B: " << si.getBeta() << "\n";
        cout << "highBitPosN: " << si.getHighBitPosN() << "\n";
        cout << "K: " << si.getK().str() << "\n";
        cout << "N: " << si.getN().str() << "\n";
        cout << "N2: " << si.getN2().str() << "\n";
        cout << "P: " << si.getP().str() << "\n";
        cout << "Q: " << si.getQ().str() << "\n";
        cout << "~2^B: " << si.getTwoToBeta().str() << "\n";
        cout << "Xp1: " << si.getXp1().str() << "\n";
        cout << "Xp2: " << si.getXp2().str() << "\n";

	/* SecureInt and Cryptosystem test area */

	Cryptosystem cs(__PQ(13)(11)(3)(), 3, __HALFTABLE, libgDir, "g", __GEN);
	SecureInt a(__E(11),cs), b(__E(3),cs), c[100];

	//aaa = Cryptosystem(__PQ()()()()__, __BETA__, __2TOBETA__, __ENC0__, __ENC1__, libgDir, "g");
	//a = SecureInt(__N(11)__,aaa); b = SecureInt(__N(3)__,aaa);
	int ai = 11;	
	int bi = 3;

	int i = 0;
	c[0] = a+b;	cout << i++ << "\n";
	c[1] = a-b;	cout << i++ << "\n";
	c[2] = a==b;	cout << i++ << "\n";
	c[3] = a!=b;	cout << i++ << "\n";
	c[4] = -a;	cout << i++ << "\n";
	c[5] = +a;	cout << i++ << "\n";
	c[6] = a*b;	cout << i++ << "\n";
	c[7] = a<<0;	cout << i++ << "\n";
	c[8] = a<<1; 	cout << i++ << "\n";
	c[9] = a<<2;	cout << i++ << "\n";
	c[10] = a<<3;	cout << i++ << "\n";
	c[11] = a<<4;	cout << i++ << "\n";
	c[12] = a<<5;	cout << i++ << "\n";
	c[13] = a<<6;	cout << i++ << "\n";
	c[14] = a<<7;	cout << i++ << "\n";
	c[15] = a<<8;	cout << i++ << "\n";
	c[16] = a>>1; 	cout << i++ << "\n";
	c[17] = a>>2;	cout << i++ << "\n";
	c[18] = (a+b)*(a-b); cout << i++ << "\n";
	c[19] = a+b*b;	cout << i++ << "\n";
	c[20] = a<<b;	cout << i++ << "\n";
	c[21] = a>>b;	cout << i++ << "\n";
	c[22] = a>b;	cout << i++ << "\n";
	c[23] = a<b;	cout << i++ << "\n";
	c[24] = a>=b;	cout << i++ << "\n";
	c[25] = a<=b;	cout << i++ << "\n";
	
	c[26] = a+ai;	cout << i++ << "\n";
	c[27] = a-ai;	cout << i++ << "\n";
	c[28] = a==ai;	cout << i++ << "\n";
	c[29] = a!=ai;	cout << i++ << "\n";
	c[30] = SecureInt(-ai,cs);	cout << i++ << "\n";
	c[31] = SecureInt(+ai,cs);	cout << i++ << "\n";
	c[32] = a*ai;	cout << i++ << "\n";
	c[33] = a<<ai;	cout << i++ << "\n";
	c[34] = a>>ai;	cout << i++ << "\n";
	c[35] = a>ai;	cout << i++ << "\n";
	c[36] = a<ai;	cout << i++ << "\n";
	c[37] = a>=ai;	cout << i++ << "\n";
	c[38] = a<=ai;	cout << i++ << "\n";

	c[39] = a+bi;	cout << i++ << "\n";
	c[40] = a-bi;	cout << i++ << "\n";
	c[41] = a==bi;	cout << i++ << "\n";
	c[42] = a!=bi;	cout << i++ << "\n";
	c[43] = SecureInt(-bi,cs);	cout << i++ << "\n";
	c[44] = SecureInt(+bi,cs);	cout << i++ << "\n";
	c[45] = a*bi;	cout << i++ << "\n";
	c[46] = a<<bi;	cout << i++ << "\n";
	c[47] = a>>bi;	cout << i++ << "\n";
	c[48] = a>bi;	cout << i++ << "\n";
	c[49] = a<bi;	cout << i++ << "\n";
	c[50] = a>=bi;	cout << i++ << "\n";
	c[51] = a<=bi;	cout << i++ << "\n";

	c[52] = ai+b;	cout << i++ << "\n";
	c[53] = ai-b;	cout << i++ << "\n";
	c[54] = ai==b;	cout << i++ << "\n";
	c[55] = ai!=b;	cout << i++ << "\n";
	c[56] = ai*b;	cout << i++ << "\n";
	c[57] = ai<<b;	cout << i++ << "\n";
	c[58] = ai>>b;	cout << i++ << "\n";
	c[59] = ai>b;	cout << i++ << "\n";
	c[60] = ai<b;	cout << i++ << "\n";
	c[61] = ai>=b;	cout << i++ << "\n";
	c[62] = ai<=b;	cout << i++ << "\n";

	c[63] = --a;	cout << i++ << "\n";
	c[64] = --b;	cout << i++ << "\n";
	c[65] = ++a;	cout << i++ << "\n";
	c[66] = ++b;	cout << i++ << "\n";

	c[67] = a>>3;	cout << i++ << "\n";
	c[68] = a>>4;	cout << i++ << "\n";
	c[69] = a>>5;	cout << i++ << "\n";

	/* Checking SecureInt results with SensitiveInformation */
	
	cout << "\nOutputs:\n";

	Unumber R, udecC[100];
	
	udecA = si.decrypt(a.getX(), &R);
	udecB = si.decrypt(b.getX(), &R);
	cout << "a\t"; printPair(udecA, a.getX());
	cout << "b\t"; printPair(udecB, b.getX());

	SecureInt t (15, cs);
	Unumber udecT = si.decrypt(t.getX(), &R);
	cout << "t\t"; printPair(udecT, t.getX());
	t = 15==t;	
	udecT = si.decrypt(t.getX(), &R);
	cout << "t\t"; printPair(udecT, t.getX());

	cout << "\n";
	for (int i = 0; i <= 69; i++)
	{
		udecC[i] = si.decrypt(c[i].getX(), &R);
		cout << i << "\t";
		printPair(udecC[i], c[i].getX());
	}

	//R.prita();
	//cs.prita();

	return 0;
}

void printPair(const Unumber dec, const Unumber enc)
{
	cout << "m: " << dec.str() << "\tx: " << enc << "\n";
}

