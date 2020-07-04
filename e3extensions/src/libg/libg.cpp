#include <iostream>

/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

/*******************************************
* Note: this G function is not secure      *
        it is merely functional            *
        use it only for testing purpose    *
********************************************/

#include "../preprocessor/big_random.h"
#include "libg.h"
#include "../unumber/unumberg.h"

//#ifndef STATIC_LIBG
	#include <fstream>
	#include <iostream>

	#define FILENAME "CS.txt"

	using namespace std;

	bool loaded = false;
//#endif

//Unumber fkf, _g, n, xp1, xp2, n2;

Unumber fkf(3480), _g(430), n(143), xp1(144), xp2(18304);
Unumber n2 = n*n;

#ifdef FAST_RANDOM
Unumber rN(0);
#endif

/* G function */
/* if the unencryption of x is less or equal zero
 * 	return the encryption of zero
 * else return the reencryption of y */	
Unumber libg(Unumber x, Unumber y)
{
	if (!loaded) loadCryptosystemParams(); // Used if libg is a shared object

/* Software libg */
#ifndef HWACC

/* Software libg */
//#ifndef STATIC_LIBG
//#endif

	Unumber ox = Unumber(x);
	ox.pow(fkf, n2);

	Unumber zero = encrypt(0);
	Unumber _y = reencrypt(y);

	if (leq(ox)) return zero;
	return _y;

/* Hardware libg */
#else
	//std::cout << "libg in\n";
	unsigned length = Unumber::HW_NUMWORDS;
	unsigned mA[length], mB[length], mC[length], mD[length];

	Unumber::exportArray(mA, length, x);
	Unumber::exportArray(mB, length, y);
	Unumber::exportArray(mC, length, n2);

	Unumber::mter_e1(mA);
	Unumber::mter_e2(mB);
	Unumber::mter_e3(mC);

	Unumber::hw_gfun();

	Unumber::mfer_e0(mD);

	Unumber r = Unumber::importArray(mD, length);

	//std::cout << "libg out\n";
	return r;
#endif
}

/* Return (x % n) */
/* It is used to make sure x < n */
Unumber congruence(Unumber x, const Unumber & n)
{
	if ( n.iszero() ) return x;

	Unumber nn(n);
	nn <<= 2;
	if (nn > x)
	{
		while (n < x) x -= n;
		return x;
	}

	x.divABRQ(n, &nn, 0);
	return nn;
}

/* Encrypt following equation x = r^N * (1 + N*k*m) % N2 */
Unumber encrypt(const Unumber & m)
{
#ifdef FAST_RANDOM
	if (rN == 0)
	{
		rN = invertibleRandom(2,n);
		rN.pow(n,n2);
	}
	else rN.mul(rN,n2);
#else
	Unumber rN = invertibleRandom(2,n);
	rN.pow(n, n2); //r^N
#endif

	Unumber gm = _g;
	// gm.pow(congruence(m, n), n2); // g^m % N2 -- replaced by the next line
	gm = (congruence(m, n) * (gm - 1) + 1) % n2; // (1 + N*k*m) % N2

	Unumber x = rN.mul(gm, n2); // r^N * (1 + N*k*m) % N2

	return x;
}

/* Leq test */
/* Return true if an open value x is less or equal than zero */
bool leq(const Unumber x)
{
	return ((x < xp1) || (xp2 < x));
}

/* Load Cryptosystem parameters from CS.txt file */
//#ifndef STATIC_LIBG
void loadCryptosystemParams()
{
	ifstream in;
	in.open(FILENAME, ifstream::in);
	stringstream buffer;
	buffer << in.rdbuf();
	string text = buffer.str();
	in.close();

	int len = 11;
	int semicolon[len];
	semicolon[0] = text.find(";") + 1;
	for (int i = 1; i < len; i++)
	{
		semicolon[i] = text.find(";", semicolon[i-1]) + 1;
	}
	//int newLine = text.find("\n") + 1;

	//string strP   = text.substr(semicolon[0], semicolon[1]-semicolon[0]-1);
	//string strQ   = text.substr(semicolon[1], semicolon[2]-semicolon[1]-1);
	//string strK   = text.substr(semicolon[2], semicolon[3]-semicolon[2]-1);
	//string strBeta	= text.substr(semicolon[3], semicolon[4]-semicolon[3]-1);
	string strFKF = text.substr(semicolon[4], semicolon[5]-semicolon[4]-1);
	string strG   = text.substr(semicolon[5], semicolon[6]-semicolon[5]-1);
	string strN   = text.substr(semicolon[6], semicolon[7]-semicolon[6]-1);
	string strXp1 = text.substr(semicolon[7], semicolon[8]-semicolon[7]-1);
	string strXp2 = text.substr(semicolon[8], semicolon[9]-semicolon[8]-1);

	//cout << text << "\n";

	//p = Unumber(strP);
	//q = Unumber(strQ);
	//k = Unumber(strK);
	fkf = Unumber(strFKF);
	_g = Unumber(strG);
	n = Unumber(strN);
	xp1 = Unumber(strXp1);
	xp2 = Unumber(strXp2);
	n2 = n*n;
	
	loaded = true;
}
//#endif

/* Reencrypt a cyphertext with a random invertible number */
/* Following the equation x' = (r^N * x) % N2 */
Unumber reencrypt(const Unumber & x)
{
#ifdef FAST_RANDOM
	if (rN == 0)
	{
		rN = invertibleRandom(2,n);
		rN.pow(n,n2);
	}
	else rN.mul(rN,n2);

	Unumber y = rN.mul(x,n2);
#else
	Unumber y = invertibleRandom(2,n);
	y.pow(n,n2);
	y = y.mul(x,n2);
#endif

	return y;
}

