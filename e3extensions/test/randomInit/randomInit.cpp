/*******************************************
*  DDD   EEEE  BBB   U  U   GG       DEBUG *
*  D  D  E     B  B  U  U  G               *
*  D  D  EEE   BBB   U  U  G GG            *
*  D  D  E     B  B  U  U  G  G            *
*  DDD   EEEE  BBB    UU    GG   2016-2017 *
********************************************/

#ifndef FSTREAM_INCLUDED
	#define FSTREAM_INCLUDED
	#include <fstream>
#endif

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

#define FILENAME "CS.txt"

using namespace std;

string libgDir = "./libg.so";
Unumber p, q, k;

void loadCryptosystemParams();
void printPair(const Unumber, const Unumber);

/*
 * P and Q must be different prime numbers
 * K and RND must not be multiple of P or Q
 */

int main()
{
	/* SecureInt and Cryptosystem test area */
	loadCryptosystemParams();
	SensitiveInformation si(p,q,k);

	Cryptosystem cs(__PQ()()()()__, 3, __2TOBETA__, __ENC0__, __ENC1__, libgDir, "libg");
	SecureInt a(__N(11)__,cs), b(__N(3)__,cs), c[20];
		
	c[0] = a+b;	cout << "0\n";
	c[1] = a-b;	cout << "1\n";
	c[2] = a==b;	cout << "2\n";
	c[3] = a!=b;	cout << "3\n";
	c[4] = -a;	cout << "4\n";
	c[5] = +a;	cout << "5\n";
	c[6] = a*b;	cout << "6\n";
	c[7] = a<<0;	cout << "7\n";
	c[8] = a<<1; 	cout << "8\n";// equivalent to a * a * ... the number of a's is (param+1).
	c[9] = a<<2;	cout << "9\n";
	c[10] = a<<3;	cout << "10\n";
	c[11] = a<<4;	cout << "11\n";
	c[12] = a<<5;	cout << "12\n";
	c[13] = a<<6;	cout << "13\n";
	c[14] = a<<7;	cout << "14\n";
	c[15] = a<<8;	cout << "15\n";
	c[16] = a>>1; 	cout << "16\n";// equivalent to subsequent div2's of a. The number of div2's is param.
	c[17] = a>>2;	cout << "17\n";
	c[18] = (a+b)*(a-b);	cout << "18\n";
	c[19] = a+b*b;	cout << "19\n";
	
	/* Checking SecureInt results with SensitiveInformation */
	
	cout << "\nOutputs:\n";

	Unumber R, udecA, udecB, udecC[20];
	
	udecA = si.decrypt(a.getX(), &R);
	udecB = si.decrypt(b.getX(), &R);
	cout << "a\t"; printPair(udecA, a.getX());
	cout << "b\t"; printPair(udecB, b.getX());

	cout << "\n";
	for (int i = 0; i <= 19; i++)
	{
		udecC[i] = si.decrypt(c[i].getX(), &R);
		cout << i << "\t";
		printPair(udecC[i], c[i].getX());
	}

	return 0;
}

void loadCryptosystemParams()
{
	ifstream in;
	in.open(FILENAME, ifstream::in);
	stringstream buffer;
	buffer << in.rdbuf();
	string text = buffer.str();
	in.close();

	int semicolon[5];
	semicolon[0] = text.find(";") + 1;
	semicolon[1] = text.find(";", semicolon[0]) + 1;
	semicolon[2] = text.find(";", semicolon[1]) + 1;
	semicolon[3] = text.find(";", semicolon[2]) + 1;
	semicolon[4] = text.find(";", semicolon[3]) + 1;
	semicolon[5] = text.find(";", semicolon[4]) + 1;
	semicolon[6] = text.find(";", semicolon[5]) + 1;
	semicolon[7] = text.find(";", semicolon[6]) + 1;
	int newLine = text.find("\n") + 1;

	string strP   = text.substr(semicolon[0], semicolon[1]-semicolon[0]-1);
	string strQ   = text.substr(semicolon[1], semicolon[2]-semicolon[1]-1);
	string strK   = text.substr(semicolon[2], semicolon[3]-semicolon[2]-1);
	string strFKF = text.substr(semicolon[3], semicolon[4]-semicolon[3]-1);
	string strG   = text.substr(semicolon[4], semicolon[5]-semicolon[4]-1);
	string strN   = text.substr(semicolon[5], semicolon[6]-semicolon[5]-1);
	string strXp1 = text.substr(semicolon[6], semicolon[7]-semicolon[6]-1);
	string strXp2 = text.substr(semicolon[7], newLine     -semicolon[7]-1);

	p = Unumber(strP);
	q = Unumber(strQ);
	k = Unumber(strK);
	/*fkf = Unumber(strFKF);
	_g = Unumber(strG);
	n = Unumber(strN);
	xp1 = Unumber(strXp1);
	xp2 = Unumber(strXp2);
	n2 = n*n;*/

	//cout << text << " [T]\n";
	cout << "PQK -> " << p.str() << " " << q.str() << " " << k.str() << "\n";
}

void printPair(const Unumber dec, const Unumber enc)
{
	cout << "m: " << dec.str() << "\tx: " << enc.str() << "\n";
}

