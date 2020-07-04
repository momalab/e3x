/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#ifndef __CRYPTOSYSTEM_H__
#define __CRYPTOSYSTEM_H__

#include <iostream>
#include "../unumber/unumberg.h"
#include <vector>

using namespace std;

#ifdef ARCH64
	#define WORD_SIZE 64
#else
	#define WORD_SIZE 32
#endif

class Cryptosystem
{
    /* Variables */
    private:
	vector<Unumber> halfTable;
	Unumber n, n2;
	
    /* Constructors */
    public:
	Cryptosystem() {}
	Cryptosystem(const Cryptosystem &);
	Cryptosystem(const string &, unsigned, const vector<string>, const string &, const string &, const string & gen = "0");
	Cryptosystem(const Unumber, unsigned, const Unumber, const Unumber, const Unumber, const string &, const string &);
	Cryptosystem(unsigned long long, unsigned, unsigned long long, unsigned long long, unsigned long long, const string &, const string &);

    /* Private functions */
    private:
	Unumber congruence(Unumber, const Unumber &);
	void init();

    /* Public functions */
    public:
	void close();
	Unumber encrypt(const Unumber &);
	Unumber g(Unumber, Unumber) const;
	unsigned getBeta() const;
	Unumber getN() const;
	Unumber getN2() const;
	Unumber getOne() const;
	Unumber getPowerOfTwo(int) const;
	Unumber getTwoToBeta() const;
	Unumber getZero() const;
	Unumber invert(Unumber) const;
	Unumber invertibleRandom() const;
	Unumber reencrypt(Unumber);
};

/************************
 *     CONSTRUCTORS     *
 ************************/

inline
Cryptosystem::Cryptosystem(const Cryptosystem & param)
{
	this->n = param.n;
	this->beta = param.beta;
	//this->twoToBeta = param.twoToBeta;
	this->halfTable = param.halfTable;
	//this->zero = param.zero;
	//this->one = param.one;
	this->libgFilename = param.libgFilename;
	this->libgFunction = param.libgFunction;
	this->gen = param.gen;
	//this->libgInit = param.libgInit;
	//this->id = param.id;

	init();
}

inline
Cryptosystem::Cryptosystem(const string & n, unsigned beta, const vector<string> halfTable, const string & libgFilename, const string & libgFunction, const string & gen)
{
	this->n = Unumber(n);
	this->beta = beta;
	//this->twoToBeta = Unumber(twoToBeta);
	convertHalfTable(halfTable);
	//this->zero = Unumber(zero);
	//this->one = Unumber(one);
	this->libgFilename = libgFilename;
	this->libgFunction = libgFunction;
	this->gen = gen;
	//this->libgInit = libgInit;
	//this->id = INVALID_ID;
	//this->id = addLocalHalfTable(localHalfTable);

	init();
}

inline
Cryptosystem::Cryptosystem(const Unumber n, unsigned beta, const Unumber twoToBeta, const Unumber zero, const Unumber one, const string & libgFilename, const string & libgFunction)
{
	this->n = n;
	this->beta = beta;
	this->twoToBeta = twoToBeta;
	this->zero = zero;
	this->one = one;
	this->libgFilename = libgFilename;
	this->libgFunction = libgFunction;
	//this->libgInit = libgInit;
	//this->id = INVALID_ID;

	init();
}

inline
Cryptosystem::Cryptosystem(unsigned long long n, unsigned beta, unsigned long long twoToBeta, unsigned long long zero, unsigned long long one, const string & libgFilename, const string & libgFunction)
{
	this->n = Unumber(n);
	this->beta = beta;
	this->twoToBeta = Unumber(twoToBeta);
	this->zero = Unumber(zero);
	this->one = Unumber(one);
	this->libgFilename = libgFilename;
	this->libgFunction = libgFunction;
	//this->libgInit = libgInit;
	//this->id = INVALID_ID;

	init();
}

#endif

