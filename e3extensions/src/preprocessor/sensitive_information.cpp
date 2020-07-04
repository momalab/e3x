/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#include "sensitive_information.h"
#include <iostream>
#include "big_random.h"

/************************
 *     CONSTRUCTORS     *
 ************************/

SensitiveInformation::SensitiveInformation(const string & p, const string & q, const string & k)
{
	this->p = Unumber(p);
	this->q = Unumber(q);
	this->k = Unumber(k);
	this->rnd = Unumber(0);

	init();
}

SensitiveInformation::SensitiveInformation(const string & p, const string & q, const string & k, const string & rnd)
{
	this->p = Unumber(p);
	this->q = Unumber(q);
	this->k = Unumber(k);
	this->rnd = Unumber(rnd);

	init();
}

SensitiveInformation::SensitiveInformation(const string & p, const string & q, const string & k, const string & rnd, unsigned beta)
{
	this->p = Unumber(p);
	this->q = Unumber(q);
	this->k = Unumber(k);
	this->rnd = Unumber(rnd);
	this->beta = beta;

	init();
}

SensitiveInformation::SensitiveInformation(const Unumber p, const Unumber q, const Unumber k)
{
	this->p = p;
	this->q = q;
	this->k = k;
	this->rnd = Unumber(0);

	init();
}

SensitiveInformation::SensitiveInformation(const Unumber p, const Unumber q, const Unumber k, const Unumber rnd)
{
	this->p = p;
	this->q = q;
	this->k = k;
	this->rnd = rnd;

	init();
}

SensitiveInformation::SensitiveInformation(const Unumber p, const Unumber q, const Unumber k, const Unumber rnd, unsigned beta)
{
	this->p = p;
	this->q = q;
	this->k = k;
	this->rnd = rnd;
	this->beta = beta;

	init();
}

SensitiveInformation::SensitiveInformation(unsigned long long p, unsigned long long q, unsigned long long k)
{
	this->p = Unumber(p);
	this->q = Unumber(q);
	this->k = Unumber(k);
	this->rnd = Unumber(0);

	init();
}

SensitiveInformation::SensitiveInformation(unsigned long long p, unsigned long long q, unsigned long long k, unsigned long long rnd)
{
	this->p = Unumber(p);
	this->q = Unumber(q);
	this->k = Unumber(k);
	this->rnd = Unumber(rnd);

	init();
}


/*****************************
 *     PRIVATE FUNCTIONS     *
 *****************************/

/* Return (x % n) */
/* It is used to make sure x < n */
Unumber SensitiveInformation::congruence(Unumber x, const Unumber & n)
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

void SensitiveInformation::init()
{
//	std::cout << "SensitiveInformation::init 0\n";
	rndN = 0;
	sneak = 1;

	//implement method similar to init(Unumber n) but calculating n inside the method
	n = p * q; // n = p * q * z;
	n2 = n * n;
	
	/* initialize high_bit_posN and high_bit_posN2 */
	a2 = b2 = high_bit_posN = high_bit_posN2 = 0;
//	std::cout << "SensitiveInformation::init 1\n";
	Unumber x = n - 1;
	while (x != 0) { x >>= 1; high_bit_posN++; }
	high_bit_posN--;
	xp1 = 2;
	xp2 = Unumber(0) - 1;
	xp2 >>= 1;

	x = n2;
	while (x != 0) { x >>= 1; high_bit_posN2++; }
	high_bit_posN2--;
//	std::cout << "SensitiveInformation::init 2\n";
	unsigned nbit = 0;
	while ((n >> ++nbit) != 1);
	a2 = (Unumber(1) << nbit);
//	std::cout << "SensitiveInformation::init 3\n";
	/* define xp1 and xp2 for Leq test */
	Unumber tpmax = (Unumber(1) << high_bit_posN) - 1;
	xp1 = n + 1;
	xp2 = n * (tpmax + 1);
//	std::cout << "SensitiveInformation::init 4\n";
	/* what does congruence do? */
	rnd = (rnd.iszero() ? invertibleRandom(2,n) : congruence(rnd, n));
	k = congruence(k, n);
	rndN = rnd;
	rndN.pow(n, n2);
//	std::cout << "SensitiveInformation::init 5\n";
	phi = (p - 1) * (q - 1);
	// (p - 1) * (q - 1) * (z - 1);

	//skipped is not prime test

	bool ik;
//	std::cout << "SensitiveInformation::init 6\n";
	if (!rnd.iszero())
	{
//		std::cout << "SensitiveInformation::init 6.1\n";
		ik = ma::invert(rndN, n, &phim1);
//		std::cout << "SensitiveInformation::init 6.2\n";
		if (!ik) throw "Cannot invert seed: " + rnd.str() + " ^N = " + rndN.str();
	}

//	std::cout << "SensitiveInformation::init 6.3\n";
	ik = ma::invert(phi, n, &phim1); // inverting by N, not N2
//	std::cout << "SensitiveInformation::init 6.4\n";
	if ( !ik ) throw "Cannot invert phi";

//	std::cout << "SensitiveInformation::init 6.5\n";
	ik = ma::invert(k, n, &km1);  // inverting by N, not N2
//	std::cout << "SensitiveInformation::init 6.6\n";
	if ( !ik ) throw "Cannot invert k";

//	std::cout << "SensitiveInformation::init 6.7\n";
	g = 1 + k * n;

//	std::cout << "SensitiveInformation::init 6.8\n";
	ik = ma::invert(n - phi, phi, &Nm1); // inverting N by phi
//	std::cout << "SensitiveInformation::init 6.9\n";
	if ( !ik ) throw "Cannot invert N";
	p1Nk1N = phim1.mul(km1, n); // modulus is N, not N2

	//skipped - bitguard
//	std::cout << "SensitiveInformation::init 7\n";
	/* Beta */
	Unumber m = n - a2;
	if (m.iszero())
	{
		if (beta && (beta < high_bit_posN)) setB2Beta(beta);
		else if (high_bit_posN > 1) setB2Beta(high_bit_posN - 1);
		else {}
	}
	else
	{
		nbit = 0;
		while ((m >> ++nbit) > 1);

		if (beta && (beta < nbit)) setB2Beta(beta);
		else
		{
			if (b2 * 2 < a2) setB2Beta(nbit);
			else setB2Beta(nbit - 1);
		}
	}
//	std::cout << "SensitiveInformation::init 8\n";
}

/* Set ~2^Beta */
void SensitiveInformation::setB2Beta(unsigned b)
{
	beta = b;
	b2 = (Unumber(1) << b);
	twoToBeta = Unumber(2);
	twoToBeta.pow(beta, n2);

	unTwoToBeta = twoToBeta;

	twoToBeta = encrypt(twoToBeta);
}

/****************************
 *     PUBLIC FUNCTIONS     *
 ****************************/

/* Calc Half Table */
void SensitiveInformation::calcHalfTable()
{
	int length = beta;
	Unumber param = unTwoToBeta;
	Unumber encParam;

	encParam = encrypt(param);
	halfTable.push_back(encParam.str());
	for (length -= 1; length >= 0; length--)
	{
		param = param / 2;
		encParam = encrypt(param);
		halfTable.push_back(encParam.str());
	}
}

/* Decrypt */
/* a is the encrypted value */
/* R is the return of the random seed */
Unumber SensitiveInformation::decrypt(Unumber a, Unumber * R)
{
	Unumber x(fkf());
	Unumber mp1(1);

	Unumber auxA (a);
	while (x != 0)
	{
		if (x.getbit(0)) mp1 = mp1.mul(auxA, n2);

		auxA = auxA.mul(auxA, n2);
		x >>= 1;
	}
	
	//return mp1;
	Unumber m = mp1 - 1;
	if (m % n != 0) throw "Bad encrypted value " + a.str();
	
	m = m / n;

    	// m is found, now calculate r
    	// first get r^N by r^N*(1+Nkm) * (1-Nkm)
    	// (1-Nkm) = g^(N-m);

	if (!R) return m;

	Unumber r = access_g();

    	r.pow(congruence(n - m, n), n2);
    	r = r.mul(a, n2);
    	r.pow(access_Nm1(), n);
	
    	// verify

    	Unumber rN = r;
    	rN.pow(n, n2);
    	Unumber y = access_g();
    	y.pow(m, n2);
	
    	y = y.mul(rN, n2);
	
    	if (a != y) throw "extract_rm - verification failed for " + a.str();

    	*R = r;
    	return m;
}

/* Encrypt following equation x = r^N * (1 + N*k*m) % N2 */
Unumber SensitiveInformation::encrypt(Unumber x)
{
	return encrypt(x, invertibleRandom(2,n));
}

/* Encrypt following equation x = r^N * (1 + N*k*m) % N2 */
Unumber SensitiveInformation::encrypt(Unumber m, Unumber r)
{
	r.pow(n, n2); //r^N
	
	Unumber gm = g;
	gm.pow(congruence(m, n), n2); // g^m % N2 -- replaced by the next line
	//gm = (congruence(m, n) * (gm - 1) + 1) % n2; // (1 + N*k*m) % N2
	
	Unumber x = r.mul(gm, n2); // r^N * (1 + N*k*m) % N2
	
	return x;
}

/* Return the fkf, used for decryption */
Unumber SensitiveInformation::fkf() const
{
    if ( n2.iszero() ) return n2;
    Unumber Nphi = n.mul(phi, n2);
    Unumber pn = p1Nk1N.mul(sneak, n2);
    return phi.mul(pn, Nphi);
}

/* Return the high bit position of N */
unsigned SensitiveInformation::getHighBitPosN() const
{
	return high_bit_posN;
}

/* Return beta */
unsigned SensitiveInformation::getBeta() const
{
	return beta;
}

/* Return Half Table */
vector<string> SensitiveInformation::getHalfTable() const
{
	return halfTable;
}

/* Return k */
Unumber SensitiveInformation::getK() const
{
	return k;
}

/* Return N */
Unumber SensitiveInformation::getN() const
{
	return n;
}

/* Return N2 */
Unumber SensitiveInformation::getN2() const
{
	return n2;
}

/* Return p */
Unumber SensitiveInformation::getP() const
{
	return p;
}

/* Return q */
Unumber SensitiveInformation::getQ() const
{
	return q;
}

/* Return ~2^Beta */
Unumber SensitiveInformation::getTwoToBeta() const
{
	return twoToBeta;
}

/* Return the lower boundary for the leq test */
Unumber SensitiveInformation::getXp1() const
{
	return xp1;
}

/* Return the upper boundary for the leq test */
Unumber SensitiveInformation::getXp2() const
{
	return xp2;
}

/* Leq test */
/* Return true if an open value x is less or equal than zeor */
bool SensitiveInformation::leq(const Unumber x) const
{
	return ((x < xp1) || (xp2 < x));
}

/* set Beta */
void SensitiveInformation::setBeta(unsigned b)
{
	if (beta && b > beta)
	{
		std::cout << "Error trying to set beta to " << b << ". Beta cannot be greater than " << beta << ". For greater beta, increase N.\n";
	}
	else
	{
		setB2Beta(b);
	}
}

