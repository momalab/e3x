//#include "statsg.h"

/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#include "cryptosystem.h"
#include <random>

/*
int Cryptosystem::idCount = 0;
vector<vector<Unumber>> Cryptosystem::halfTable;
#ifdef FAST_RANDOM
vector <Unumber> Cryptosystem::rndN;
#endif
int Cryptosystem::calango = 0;

/*****************************
 *     PRIVATE FUNCTIONS     *
 *****************************/
/*
int Cryptosystem::addLocalHalfTable(vector<string> localHalfTable)
{
	if (localHalfTable.empty()) return INVALID_ID;
	/*{
		if (gen == 0) throw "Half table can only be empty if the generator is valid.";
		else 
	

	if (localHalfTable.size() <= beta

	vector<Unumber> newHalfTable;
	for (unsigned i = 0; i < localHalfTable.size(); i++)
	{
		newHalfTable.push_back(Unumber(localHalfTable[i]));
	}

	halfTable.push_back(newHalfTable);

#ifdef FAST_RANDOM
	rndN.push_back(0);
#endif

	return idCount++;
}
*/
void Cryptosystem::calcHalfTable()
{
	unsigned length = beta;
	vector<Unumber> newHalfTable;
	Unumber param = twoToBeta;

	for (length -= 1; length > 0; length--)
	{
		param = half(param);
		newHalfTable.push_back(param);
	}

	halfTable = newHalfTable;
}

/* Return (x % n) */
/* It is used to make sure x < n */
Unumber Cryptosystem::congruence(Unumber x, const Unumber & n)
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

/* Convert Half Table from string to Unumber */
void Cryptosystem::convertHalfTable(vector<string> strHalfTable)
{
	for (unsigned i = 0; i < strHalfTable.size(); i++) halfTable.push_back(Unumber(strHalfTable[i]));
}

Unumber Cryptosystem::half(Unumber x)
{
	// sum = ~0
	Unumber sum = zero;

	// p2 = ~1
	Unumber p2 = one;

	// Other variables
	Unumber y, my;

	// Inverse of param
	Unumber mx = invert(x);

	// Beta times
	unsigned b = beta;

	while (b-- > 0)
	{
		// y = p2 + p2 - x
		y = p2.mul(p2, n2);
		y = y.mul(mx, n2);

		// |y| = G(y,y)+G(-y,-y)
		my = invert(y);
		y = g(y,y);
		my = g(my,my);
		y = y.mul(my,n2);
		
		// y = G(|y|,~1)
		y = g(y,one);

		// y = G(~1-y,p2)
		my = invert(y);
		y = my.mul(one,n2);
		y = g(y,p2);

		// sum = sum + y
		sum = sum.mul(y,n2);

		// p2 = p2 + p2
		p2 = p2.mul(p2,n2);
	}

	return sum;
}

/* Initialize */
/* Find the high bit position of (n-1) */
/* Linking external G function */
void Cryptosystem::init()
{
	n2 = n * n;

	high_bit_posN = 0;
	Unumber x = n - 1;
	while (x != 0) { x >>= 1; high_bit_posN++; }
	high_bit_posN--;

	r = 0;

	/*x = n2;
	while (x != 0) { x >>= 1; high_bit_posN2++; }
	high_bit_posN2--;*/

	/* loading external G function */
#ifndef STATIC_LIBG
	using std::cerr;
 
	// Find library and associate to handle
	
	libgHandle = dlopen(libgFilename.c_str(), RTLD_NOW);
	if (!libgHandle)
	{
		cerr << dlerror() << "\n";
		exit(1);
	}
	dlerror();

	// Find G function and link it
	libg = (libG_t) dlsym(libgHandle, libgFunction.c_str());
	const char *dlsym_error = dlerror();
	if (dlsym_error)
	{
		cerr << dlsym_error << "\n";
		dlclose(libgHandle);
		exit(1);
	}
#endif

	if (halfTable.empty())
	{
		if (gen == 0) throw "Half table can only be empty if the generator is valid.\n";
		else
		{
			twoToBeta = 1;
			twoToBeta = 1 << beta;
			twoToBeta = encrypt(twoToBeta);
			calcHalfTable();
		}
	} else
	{
		twoToBeta = halfTable[0];
		if (halfTable.size() <= beta) calcHalfTable();
	}
	one = halfTable[halfTable.size()-1];
	zero = invert(one);
	zero = zero.mul(one, n2);
}

/****************************
 *     PUBLIC FUNCTIONS     *
 ****************************/

void Cryptosystem::close()
{
#ifndef STATIC_LIBG
	dlclose(libgHandle);
#endif
}

/* Encrypt following equation x = r^N * (1 + N*k*m) % N2 */
Unumber Cryptosystem::encrypt(const Unumber & m)
{
	if (gen == 0) throw "Generator not initialized\n";

#ifdef FAST_RANDOM
	if (r == 0)
	{
		r = invertibleRandom();
		r.pow(n,n2);
	}
	else r.mul(r,n2);
	Unumber rN = r;
#else
	Unumber rN = invertibleRandom();
	rN.pow(n,n2);
#endif
	Unumber gm = (congruence(m, n) * (gen - 1) + 1) % n2; // (1 + N*k*m) % N2
	Unumber x = rN.mul(gm, n2); // r^N * (1 + N*k*m) % N2
	return x;
}

/* G function */
Unumber Cryptosystem::g(Unumber x, Unumber y) const
{
	/*stats_g_counter++;*/
	return libg(x, y);
}

/* Return Beta */
unsigned Cryptosystem::getBeta() const
{
	return beta;
}

/* Return N */
Unumber Cryptosystem::getN() const
{
	return n;
}

/* Return N2 */
Unumber Cryptosystem::getN2() const
{
	return n2;
}

/* Return reencrypted one */
Unumber Cryptosystem::getOne() const
{
	//return reencrypt(one);
	return one;
}

Unumber Cryptosystem::getPowerOfTwo(int index) const
{
	return halfTable[beta-index];
}

/* Return reencrypted 2^Beta */
Unumber Cryptosystem::getTwoToBeta() const
{
	return twoToBeta;
}

/* Return reencrypted zero */
Unumber Cryptosystem::getZero() const
{
	//return reencrypt(zero);
	return zero;
}

Unumber Cryptosystem::invert(Unumber number) const
{
	Unumber inv;
	bool k = ma::invert(number, n2, &inv);
	if ( !k )
	{
		std::cout << "Inverse does not exist.\n";
		throw "Inverse does not exist.\n";
	}

	return inv;
}

/* Invertible Random */
/* Generate an invetible random number */
Unumber Cryptosystem::invertibleRandom() const
{
	std::random_device rd;
#ifdef ARCH64
	std::mt19937_64 mt(rd());
#else
	std::mt19937 mt(rd());
#endif
	
	Unumber number(0);
	while (true)
	{
		number = 0;
		unsigned count = 0;
		while (count < high_bit_posN)
		{
			count += WORD_SIZE;
			number <<= WORD_SIZE;
			number += mt();
		}

		/* "count - high_bit_posN - 1" guarantees random numbers [1,n-1].
		 * However, any random number > (n-1) needs to be ignored.
		 * If "count - high_bit_posN" is used instead,
		 * the range of random numbers is [1,x], where x < (n-1),
		 * but it is faster. */
		unsigned shift = count - high_bit_posN - 1;
		number >>= shift;

		/* the number is valid if it is a number in the range [1,n-1]
		 * and its gcd with n is one */
		if ((number < n) && (ma::gcd(number, n) == 1)) break;
	}

	return number;
}

/* Reencrypt a cyphertext with a random invertible number */
/* Following the equation x' = (r^N * x) % N2 */
Unumber Cryptosystem::reencrypt(Unumber x)
{
#ifdef FAST_RANDOM
	if (r == 0)
	{
		r = invertibleRandom();
		r.pow(n,n2);
	}
	else
	{
		r.mul(r,n2);
	}

	Unumber y = r.mul(x,n2);
#else
	Unumber y = invertibleRandom();
	y.pow(n,n2);
	y.mul(x,n2);
#endif

	return y;
}
/*
void Cryptosystem::prita()
{
	std::cout << "G calls: " << stats_g_counter << "\n";
}
*/

