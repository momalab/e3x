/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#include "securering.h"

/*********************
 *     OPERATORS     *
 *********************/

/* Encrypted addition */
void SecureRing::operator+= (const SecureRing & param)
{
	x.eradd(param.x);
}

/* Encrypted subtraction */
void SecureRing::operator-= (const SecureRing & param)
{
	x.ersub(param.x);
}

/* Encrypted multiplication */
void SecureRing::operator*= (const SecureRing& param)
{
	x.emuls(param.x);
}

/* Shift left */
void SecureRing::operator<<= (const SecureRing& param)
{
	x.esll(param.x);
}

/* Shift right */
void SecureRing::operator>>= (const SecureRing& param)
{
	x.esra(param.x);
}

/* Encrypted increment */
SecureRing SecureRing::operator++ ()
{
	x.einc();
}

/* Encrypted decrement */
/* Equivalent to a inverse followed by modular multiplication */
SecureRing SecureRing::operator-- ()
{
	x.edec();
}

SecureRing operator! (const SecureRing & n1)
{
	Unumber cmp (n1.x);
	cmp.elnot();
	return SecureRing(cmp);
}

/* Addition */
SecureRing operator+ (const SecureRing & n1, const SecureRing & n2)
{
	SecureRing r(n1); r += n2; return r;
}

/* Subtraction */
SecureRing operator- (const SecureRing & n1, const SecureRing & n2)
{
	SecureRing r(n1); r -= n2; return r;
}

/* Multiplication */
SecureRing operator* (const SecureRing & n1, const SecureRing & n2)
{
	SecureRing r(n1); r *= n2; return r;
}

/* Shift left */
SecureRing operator<< (const SecureRing & n1, const SecureRing & shift)
{
	SecureRing r(n1); r <<= shift; return r;
}

/* Shift right */
SecureRing operator>> (const SecureRing & n1, const SecureRing & shift)
{
	SecureRing r(n1); r >>= shift; return r;
}

/* Equal */
/* Compare if two encrypted numbers are equal */
SecureRing operator== (const SecureRing & n1, const SecureRing & n2)
{
	Unumber cmp;
	cmp.eeq(n1.x, n2.x);
	return SecureRing(cmp);
}

/* Different */
/* Compare if two encrypted numbers are different */
SecureRing operator!= (const SecureRing & n1, const SecureRing & n2)
{
	Unumber cmp;
	cmp.ene(n1.x, n2.x);
	return SecureRing(cmp);
}

/* Different */
/* Compare if two encrypted numbers are different */
SecureRing operator> (const SecureRing & n1, const SecureRing & n2)
{
	Unumber cmp;
	cmp.egts(n1.x, n2.x);
	return SecureRing(cmp);
}

/* Different */
/* Compare if two encrypted numbers are different */
SecureRing operator< (const SecureRing & n1, const SecureRing & n2)
{
	Unumber cmp;
	cmp.elts(n1.x, n2.x);
	return SecureRing(cmp);
}

/* Different */
/* Compare if two encrypted numbers are different */
SecureRing operator>= (const SecureRing & n1, const SecureRing & n2)
{
	Unumber cmp;
	cmp.eges(n1.x, n2.x);
	return SecureRing(cmp);
}

/* Different */
/* Compare if two encrypted numbers are different */
/* Return encrypted one if true, and encrypted zero otherwise */
SecureRing operator<= (const SecureRing & n1, const SecureRing & n2)
{
	Unumber cmp;
	cmp.eles(n1.x, n2.x);
	return SecureRing(cmp);
}


/************************************
 *     PRIVATE OBJECT FUNCTIONS     *
 ************************************/


/***********************************
 *     PUBLIC OBJECT FUNCTIONS     *
 ***********************************/

/* Return the Cryptosystem */
/*Cryptosystem SecureRing::getCryptosystem() const
{
	return cryptosystem;
}*/

/* Return the cyphertext (x) */
Unumber SecureRing::getX() const
{
	return x;
}

SecureRing SecureRing::ternary(const SecureRing & n1, const SecureRing & n2)
{
	x.ecmov(n1.x, n2.x);
}

/* Return the cyphertext in string format */
string SecureRing::str(unsigned base) const
{
	return x.str(base);
}


/************************************
 *     PRIVATE STATIC FUNCTIONS     *
 ************************************/


/***********************************
 *     PUBLIC STATIC FUNCTIONS     *
 ***********************************/

void SecureRing::setKey(Unumber pri, Unumber pub, Unumber mod, unsigned esize, unsigned dsize)
{
	Unumber::setKey(pri, pub, mod, esize, dsize);
}

SecureRing SecureRing::encrypt(unsigned long long m)
{
	Unumber x(m);
	x.enc();
	return SecureRing(x);
}
