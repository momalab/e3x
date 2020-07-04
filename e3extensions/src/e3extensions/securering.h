/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#ifndef __SecureRing_H__
#define __SecureRing_H__

#include <iostream>
#include "../unumber/unumberg.h"

class SecureRing
{
    /* Variables */
    private:
	Unumber x;

    public:
	enum StringType { Binary, Decimal };

    /* Constructors */
    public:
	SecureRing() {}
	SecureRing(const SecureRing &);
	SecureRing(const Unumber);
	SecureRing(const string &);

    /* Operators */
    public:
	void operator+= (const SecureRing &);
	//void operator+= (unsigned long long);
	void operator-= (const SecureRing &);
	//void operator-= (unsigned long long);
	void operator*= (const SecureRing &);
	//void operator*= (unsigned long long);
	void operator<<= (const SecureRing &);
	//void operator<<= (unsigned);
	void operator>>= (const SecureRing &);
	//void operator>>= (unsigned);
	SecureRing operator++ ();
	//SecureRing operator++ (int);
	SecureRing operator-- ();
	//SecureRing operator-- (int);
	
	//friend SecureRing operator+ (const SecureRing & n1) { return n1; }
	//friend SecureRing operator- (const SecureRing & n1) { return SecureRing::invert(n1); }

	friend SecureRing operator! (const SecureRing &);

	friend SecureRing operator+ (const SecureRing &, const SecureRing &);
	//friend SecureRing operator+ (SecureRing &, unsigned long long);
	//friend SecureRing operator+ (unsigned long long, SecureRing &);

	friend SecureRing operator- (const SecureRing &, const SecureRing &);
	//friend SecureRing operator- (SecureRing &, unsigned long long);
	//friend SecureRing operator- (unsigned long long, SecureRing &);

	friend SecureRing operator* (const SecureRing &, const SecureRing &);
	//friend SecureRing operator* (const SecureRing &, unsigned long long);
	//friend SecureRing operator* (unsigned long long, const SecureRing &);

	friend SecureRing operator<< (const SecureRing &, const SecureRing &);
	//friend SecureRing operator<< (const SecureRing &, unsigned);
	//friend SecureRing operator<< (unsigned long long, SecureRing &);

	friend SecureRing operator>> (const SecureRing &, const SecureRing &);
	//friend SecureRing operator>> (const SecureRing &, unsigned);
	//friend SecureRing operator>> (unsigned long long, SecureRing &);

	friend SecureRing operator== (const SecureRing &, const SecureRing &);
	//friend SecureRing operator== (SecureRing &, unsigned long long);
	//friend SecureRing operator== (unsigned long long, SecureRing &);

	friend SecureRing operator!= (const SecureRing &, const SecureRing &);
	//friend SecureRing operator!= (SecureRing &, unsigned long long);
	//friend SecureRing operator!= (unsigned long long, SecureRing &);

	friend SecureRing operator> (const SecureRing &, const SecureRing &);
	//friend SecureRing operator> (SecureRing &, unsigned long long);
	//friend SecureRing operator> (unsigned long long, SecureRing &);

	friend SecureRing operator< (const SecureRing &, const SecureRing &);
	//friend SecureRing operator< (SecureRing &, unsigned long long);
	//friend SecureRing operator< (unsigned long long, SecureRing &);

	friend SecureRing operator>= (const SecureRing &, const SecureRing &);
	//friend SecureRing operator>= (SecureRing &, unsigned long long);
	//friend SecureRing operator>= (unsigned long long, SecureRing &);

	friend SecureRing operator<= (const SecureRing &, const SecureRing &);
	//friend SecureRing operator<= (SecureRing &, unsigned long long);
	//friend SecureRing operator<= (unsigned long long, SecureRing &);
	
    /* Private object functions */
    private:

    /* Public object functions */
    public:
	//Cryptosystem getCryptosystem() const;
	Unumber getX() const;
	SecureRing ternary(const SecureRing &, const SecureRing &);
	string str(unsigned base=10) const;

    /* Private static functions */
    private:

    /* Public static functions */
    public:
	static void setKey(Unumber, Unumber, Unumber, unsigned, unsigned);
	static SecureRing encrypt(unsigned long long);
};

/************************
 *     CONSTRUCTORS     *
 ************************/

inline
SecureRing::SecureRing(const SecureRing & param)
{
	this->x = param.x;
}

inline
SecureRing::SecureRing(const Unumber x)
{
	this->x = x;
}

inline
SecureRing::SecureRing(const string & s)
{
	this->x = Unumber(s);
}

#endif

