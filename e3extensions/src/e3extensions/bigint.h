/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#ifndef __SECUREINT_H__
#define __SECUREINT_H__

//#include "cryptosystem.h"
#include <iostream>
#include "../unumber/unumberg.h"

class SecureInt
{
    /* Variables */
    private:
	Unumber x;
	//Cryptosystem cryptosystem;

    public:
	enum StringType { Binary, Decimal };

    /* Constructors */
    public:
	SecureInt() {}
	SecureInt(const SecureInt &);
/*	SecureInt(const Unumber, const Cryptosystem &);
	SecureInt(const string &, const Cryptosystem &);
	SecureInt(const string &, unsigned, const Cryptosystem &);
	SecureInt(const string &, StringType, const Cryptosystem &);
	SecureInt(const string &, Unumber::StringType, const Cryptosystem &);
	SecureInt(unsigned long long, Cryptosystem &);*/
	SecureInt(const Unumber);
	SecureInt(const string &);

    /* Operators */
    public:
	void operator+= (const SecureInt &);
	//void operator+= (unsigned long long);
	void operator-= (const SecureInt &);
	//void operator-= (unsigned long long);
	void operator*= (const SecureInt &);
	//void operator*= (unsigned long long);
	void operator<<= (const SecureInt &);
	//void operator<<= (unsigned);
	void operator>>= (const SecureInt &);
	//void operator>>= (unsigned);
	void operator^= (const SecureInt &);
    void operator&= (const SecureInt &);
	void operator|= (const SecureInt &);
	SecureInt operator++ ();
	SecureInt operator++ (int);
	SecureInt operator-- ();
	//SecureInt operator-- (int);

	//friend SecureInt operator+ (const SecureInt & n1) { return n1; }
	//friend SecureInt operator- (const SecureInt & n1) { return SecureInt::invert(n1); }

	friend SecureInt operator! (const SecureInt &);

	friend SecureInt operator+ (const SecureInt &, const SecureInt &);
	//friend SecureInt operator+ (SecureInt &, unsigned long long);
	//friend SecureInt operator+ (unsigned long long, SecureInt &);

	friend SecureInt operator- (const SecureInt &, const SecureInt &);
	//friend SecureInt operator- (SecureInt &, unsigned long long);
	//friend SecureInt operator- (unsigned long long, SecureInt &);

	friend SecureInt operator* (const SecureInt &, const SecureInt &);
	//friend SecureInt operator* (const SecureInt &, unsigned long long);
	//friend SecureInt operator* (unsigned long long, const SecureInt &);

	friend SecureInt operator<< (const SecureInt &, const SecureInt &);
	//friend SecureInt operator<< (const SecureInt &, unsigned);
	//friend SecureInt operator<< (unsigned long long, SecureInt &);

	friend SecureInt operator>> (const SecureInt &, const SecureInt &);
	//friend SecureInt operator>> (const SecureInt &, unsigned);
	//friend SecureInt operator>> (unsigned long long, SecureInt &);

	friend SecureInt operator^ (const SecureInt &, const SecureInt &);
    friend SecureInt operator& (const SecureInt &, const SecureInt &);
	friend SecureInt operator| (const SecureInt &, const SecureInt &);

	friend SecureInt operator== (const SecureInt &, const SecureInt &);
	//friend SecureInt operator== (SecureInt &, unsigned long long);
	//friend SecureInt operator== (unsigned long long, SecureInt &);

	friend SecureInt operator!= (const SecureInt &, const SecureInt &);
	//friend SecureInt operator!= (SecureInt &, unsigned long long);
	//friend SecureInt operator!= (unsigned long long, SecureInt &);

	friend SecureInt operator> (const SecureInt &, const SecureInt &);
	//friend SecureInt operator> (SecureInt &, unsigned long long);
	//friend SecureInt operator> (unsigned long long, SecureInt &);

	friend SecureInt operator< (const SecureInt &, const SecureInt &);
	//friend SecureInt operator< (SecureInt &, unsigned long long);
	//friend SecureInt operator< (unsigned long long, SecureInt &);

	friend SecureInt operator>= (const SecureInt &, const SecureInt &);
	//friend SecureInt operator>= (SecureInt &, unsigned long long);
	//friend SecureInt operator>= (unsigned long long, SecureInt &);

	friend SecureInt operator<= (const SecureInt &, const SecureInt &);
	//friend SecureInt operator<= (SecureInt &, unsigned long long);
	//friend SecureInt operator<= (unsigned long long, SecureInt &);

    /* Private object functions */
    private:

    /* Public object functions */
    public:
	//Cryptosystem getCryptosystem() const;
	Unumber getX() const;
	void ror (const SecureInt &);
	string str(unsigned base=10) const;
	SecureInt mac(const SecureInt &, const SecureInt &);
	SecureInt ternary(const SecureInt &, const SecureInt &);

    /* Private static functions */
    private:

    /* Public static functions */
    public:
	static void setKey(Unumber, Unumber, Unumber, unsigned, unsigned);
	static void setControl(unsigned);
	static SecureInt encrypt(unsigned long long);
	static SecureInt randomp2(unsigned);
	static SecureInt ror (const SecureInt &, const SecureInt &);
#ifdef HWACC
    static void exportArray(unsigned[], unsigned, SecureInt);
	static SecureInt importArray(unsigned[], unsigned);
#endif
};

/************************
 *     CONSTRUCTORS     *
 ************************/

inline
SecureInt::SecureInt(const SecureInt & param)
{
	this->x = param.x;
	//this->cryptosystem = param.cryptosystem;
}
/*
inline
SecureInt::SecureInt(const Unumber x, const Cryptosystem & cryptosystem)
{
	this->x = x;
	this->cryptosystem = cryptosystem;
}

inline
SecureInt::SecureInt(const string & s, const Cryptosystem & cryptosystem)
{
	this->x = Unumber(s);
	this->cryptosystem = cryptosystem;
}

inline
SecureInt::SecureInt(const string & s, unsigned base, const Cryptosystem & cryptosystem)
{
	this->x = Unumber(s, base);
	this->cryptosystem = cryptosystem;
}

inline
SecureInt::SecureInt(const string & s, StringType st, const Cryptosystem & cryptosystem)
{
	switch (st)
	{
		case Binary: this->x = Unumber(s, Unumber::Binary); break;
		case Decimal: this->x = Unumber(s, Unumber::Decimal); break;
		default: this->x = Unumber(s, Unumber::Decimal); break;
	}

	this->cryptosystem = cryptosystem;
}

inline
SecureInt::SecureInt(const string & s, Unumber::StringType st, const Cryptosystem & cryptosystem)
{
	switch (st)
	{
		case Unumber::Binary: this->x = Unumber(s, Unumber::Binary); break;
		case Unumber::Decimal: this->x = Unumber(s, Unumber::Decimal); break;
		default: this->x = Unumber(s, Unumber::Decimal); break;
	}

	this->cryptosystem = cryptosystem;
}

inline
SecureInt::SecureInt(unsigned long long param, Cryptosystem & cryptosystem)
{
	Unumber x;
	x = cryptosystem.encrypt(param);

	this->x = x;
	this->cryptosystem = cryptosystem;
}
*/
inline
SecureInt::SecureInt(const Unumber x)
{
	this->x = x;
}

inline
SecureInt::SecureInt(const string & s)
{
	this->x = Unumber(s);
}

#endif
