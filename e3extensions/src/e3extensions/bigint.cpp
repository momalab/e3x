/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#include "bigint.h"

/*********************
 *     OPERATORS     *
 *********************/

/* Encrypted addition */
void SecureInt::operator+= (const SecureInt & param)
{
	x.add(param.x);
}

/* Encrypted subtraction */
void SecureInt::operator-= (const SecureInt & param)
{
	x.sub(param.x);
}

/* Encrypted multiplication */
void SecureInt::operator*= (const SecureInt& param)
{
	x.muls(param.x);
}

/* Shift left */
void SecureInt::operator<<= (const SecureInt& param)
{
	x.sll(param.x);
}

/* Shift right */
void SecureInt::operator>>= (const SecureInt& param)
{
	x.sra(param.x);
}

/* Rotate right */
void SecureInt::ror (const SecureInt& param)
{
	x.ror(param.x);
}

/* Exclusive or */
void SecureInt::operator^= (const SecureInt& param)
{
	x.pxor(param.x);
}

/* Bitwise and */
void SecureInt::operator&= (const SecureInt& param)
{
	// x.pand(param.x);
}

/* Bitwise or */
void SecureInt::operator|= (const SecureInt& param)
{
	x.por(param.x);
}

/* Encrypted increment (pre-fixed) */
SecureInt SecureInt::operator++ ()
{
	x.inc();
}

/* Encrypted increment (post-fixed) */
SecureInt SecureInt::operator++ (int)
{
	x.inc();
}

/* Encrypted decrement */
/* Equivalent to a inverse followed by modular multiplication */
SecureInt SecureInt::operator-- ()
{
	x.dec();
}

SecureInt operator! (const SecureInt & n1)
{
	Unumber cmp (n1.x);
	cmp.lnot();
	return SecureInt(cmp);
}

/* Addition */
SecureInt operator+ (const SecureInt & n1, const SecureInt & n2)
{
	SecureInt r(n1); r += n2; return r;
}

/* Subtraction */
SecureInt operator- (const SecureInt & n1, const SecureInt & n2)
{
	SecureInt r(n1); r -= n2; return r;
}

/* Multiplication */
SecureInt operator* (const SecureInt & n1, const SecureInt & n2)
{
	SecureInt r(n1); r *= n2; return r;
}

/* Shift left */
SecureInt operator<< (const SecureInt & n1, const SecureInt & shift)
{
	SecureInt r(n1); r <<= shift; return r;
}

/* Shift right */
SecureInt operator>> (const SecureInt & n1, const SecureInt & shift)
{
	SecureInt r(n1); r >>= shift; return r;
}

/* Rotate right */
SecureInt SecureInt::ror (const SecureInt & n1, const SecureInt & shift)
{
	SecureInt r(n1); r.ror(shift); return r;
}

/* Exclusive or */
SecureInt operator^ (const SecureInt & n1, const SecureInt & shift)
{
	SecureInt r(n1); r ^= shift; return r;
}

/* Bitwise and */
SecureInt operator& (const SecureInt & n1, const SecureInt & shift)
{
	SecureInt r(n1); r &= shift; return r;
}

/* Bitwise or */
SecureInt operator| (const SecureInt & n1, const SecureInt & shift)
{
	SecureInt r(n1); r |= shift; return r;
}

/* Equal */
/* Compare if two encrypted numbers are equal */
SecureInt operator== (const SecureInt & n1, const SecureInt & n2)
{
	Unumber cmp;
	cmp.eq(n1.x, n2.x);
	return SecureInt(cmp);
}

/* Different */
/* Compare if two encrypted numbers are different */
SecureInt operator!= (const SecureInt & n1, const SecureInt & n2)
{
	Unumber cmp;
	cmp.ne(n1.x, n2.x);
	return SecureInt(cmp);
}

/* Different */
/* Compare if two encrypted numbers are different */
SecureInt operator> (const SecureInt & n1, const SecureInt & n2)
{
	Unumber cmp;
	cmp.gts(n1.x, n2.x);
	return SecureInt(cmp);
}

/* Different */
/* Compare if two encrypted numbers are different */
SecureInt operator< (const SecureInt & n1, const SecureInt & n2)
{
	Unumber cmp;
	cmp.lts(n1.x, n2.x);
	return SecureInt(cmp);
}

/* Different */
/* Compare if two encrypted numbers are different */
SecureInt operator>= (const SecureInt & n1, const SecureInt & n2)
{
	Unumber cmp;
	cmp.ges(n1.x, n2.x);
	return SecureInt(cmp);
}

/* Different */
/* Compare if two encrypted numbers are different */
/* Return encrypted one if true, and encrypted zero otherwise */
SecureInt operator<= (const SecureInt & n1, const SecureInt & n2)
{
	Unumber cmp;
	cmp.les(n1.x, n2.x);
	return SecureInt(cmp);
}

/************************************
 *     PRIVATE OBJECT FUNCTIONS     *
 ************************************/


/***********************************
 *     PUBLIC OBJECT FUNCTIONS     *
 ***********************************/

/* Return the Cryptosystem */
/*Cryptosystem SecureInt::getCryptosystem() const
{
	return cryptosystem;
}*/

/* Return the cyphertext (x) */
Unumber SecureInt::getX() const
{
	return x;
}

SecureInt SecureInt::mac(const SecureInt & n1, const SecureInt & n2)
{
	x.macs(n1.x, n2.x);
}

SecureInt SecureInt::ternary(const SecureInt & n1, const SecureInt & n2)
{
	x.cmov(n1.x, n2.x);
}

/* Return the cyphertext in string format */
string SecureInt::str(unsigned base) const
{
	return x.str(base);
}


/************************************
 *     PRIVATE STATIC FUNCTIONS     *
 ************************************/


/***********************************
 *     PUBLIC STATIC FUNCTIONS     *
 ***********************************/

void SecureInt::setKey(Unumber pri, Unumber pub, Unumber mod, unsigned esize, unsigned dsize)
{
	Unumber::setKey(pri, pub, mod, esize, dsize);
}

void SecureInt::setControl(unsigned control)
{
	Unumber::setControl(control);
}

SecureInt SecureInt::encrypt(unsigned long long m)
{
	Unumber x(m);
	x.enc();
	return SecureInt(x);
}

SecureInt SecureInt::randomp2(unsigned l)
{
	Unumber x;
	x.randomp2(l);
	return SecureInt(x);
}
#ifdef HWACC
void SecureInt::exportArray(unsigned arr[], unsigned length, SecureInt s)
{
	Unumber::exportArray(arr, length, s.x);
}

SecureInt SecureInt::importArray(unsigned arr[], unsigned length)
{
	Unumber x = Unumber::importArray(arr, length);
	return SecureInt(x);
}
#endif
