#include <iostream>
#include <istream>
#include "unumberz.h"
#include <stdlib.h>

const bool NP_DBG = false;

Unumber Unumber::MOD_VALUE = 0;

mpz_t Unumber::n;
mpz_t Unumber::n2;
mpz_t Unumber::g;
mpz_t Unumber::phi;
mpz_t Unumber::mi;
mpz_t Unumber::one;

unsigned Unumber::ees = 0;
unsigned Unumber::eds = 0;

inline void Unumber::init_mod_value()
{
    if ( MOD_VALUE == 0 )
    {
        Unumber a(1);
        a <<= MOD_POWER;
        MOD_VALUE = a;
    }
}

void Unumber::neg()
{
    if (z >= 0)
        return;

    if (NP_DBG) std::cout << "CCC " << ("mpz negative [" + str() + "] -> ");
    init_mod_value();

    while (z < 0)
        *this += MOD_VALUE;

    if (NP_DBG) std::cout << ("[" + str() + "]") << '\n';
}

void Unumber::pos()
{
    init_mod_value();

    if (z < MOD_VALUE.z)
        return;

    if (NP_DBG) std::cout << "CCC " << ("mpz positive [" + str() + "] -> ");

    while (z >= MOD_VALUE.z)
        *this -= MOD_VALUE;

    if (NP_DBG) std::cout << ("[" + str() + "]") << '\n';
}

Unumber::Unumber(unsigned long long x): z((unsigned long)(x)) {}
Unumber::Unumber(): z(0) {}

void Unumber::operator*=(const Unumber & n) { z *= n.z; }
void Unumber::operator+=(const Unumber & n) { z += n.z; pos(); }
void Unumber::operator-=(const Unumber & n) { z -= n.z; neg(); }
void Unumber::operator%=(const Unumber & n) { z %= n.z; }
void Unumber::operator/=(const Unumber & n) { z /= n.z; }

Unumber & Unumber::operator++() { z += 1; return *this; }
Unumber & Unumber::operator--() { z -= 1; return *this; }

bool Unumber::iszero() const { return z == 0; }

string Unumber::str(unsigned base) const { return z.get_str(base); }

unsigned long long Unumber::to_ull() const { return z.get_ui(); }

void Unumber::operator<<=(int b) { mpz_mul_2exp (z.get_mpz_t(), z.get_mpz_t(), b); }
void Unumber::operator>>=(int b) { mpz_div_2exp (z.get_mpz_t(), z.get_mpz_t(), b); }

bool operator<(const Unumber & n1, const Unumber & n2) { return n1.z < n2.z; }

Unumber::Unumber(const string & s, Unumber::StringType st)
{
/*
    if ( st == Decimal ) z = s;
    if ( st == Binary ) throw "GMP binary initialization not implemented";
*/
	unsigned int base = 0;
	switch ( st )
	{
		case Decimal: base = 10; break;
		case Binary: base = 2; break;
		case Hexadecimal: base = 16; break;
	}
	mpz_set_str(z.get_mpz_t(), s.c_str(), base);
}

Unumber::Unumber(const string & s, unsigned int base)
{
	mpz_set_str(z.get_mpz_t(), s.c_str(), base);
/*	if ( base == 10 ) z = s;
	if ( base == 2 ) throw "GMP binary initialization not implemented";
*/
}

Unumber::Unumber(const Unumber & n)
{
	z = n.str();
}

Unumber Unumber::div(const Unumber & d, Unumber & q) const
{
    Unumber r;
    mpz_fdiv_qr (q.z.get_mpz_t(), r.z.get_mpz_t(), z.get_mpz_t(), d.z.get_mpz_t());
    return r;
}

void Unumber::divABRQ(const Unumber & d, Unumber * r, Unumber * q) const
{
    Unumber m;

    if (q)
        mpz_fdiv_qr (q->z.get_mpz_t(), m.z.get_mpz_t(), z.get_mpz_t(), d.z.get_mpz_t());
    else
        mpz_fdiv_r (m.z.get_mpz_t(), z.get_mpz_t(), d.z.get_mpz_t());

    if (r) *r = m;
}

Unumber Unumber::mul(const Unumber & b, const Unumber & m) const
{
    Unumber r;
    mpz_mul(r.z.get_mpz_t(), z.get_mpz_t(), b.z.get_mpz_t());
    mpz_mod(r.z.get_mpz_t(), r.z.get_mpz_t(), m.z.get_mpz_t());
    return r;
}

unsigned Unumber::Unumber::getbit(int b) const { return mpz_tstbit(z.get_mpz_t(), b); }

void Unumber::setbit1(int b)
{
    if (b)
        mpz_setbit(z.get_mpz_t(), b);
    else
        mpz_clrbit(z.get_mpz_t(), b);
}


std::istream & operator>>(std::istream & is, Unumber & n)
{
    std::string s; is >> s;

    if(!s.empty() && !!is )
    {
        Unumber u(s, Unumber::Decimal);
        n.swap(u);
    }

    return is;
}

void Unumber::pow(Unumber e, const Unumber & mod)
{
    mpz_powm(z.get_mpz_t(), z.get_mpz_t(), e.z.get_mpz_t(), mod.z.get_mpz_t());
}

void Unumber::decrypt(mpz_t m, const mpz_t c)
{
	mpz_init(m);
	mpz_powm(m, c, Unumber::phi, Unumber::n2);
	mpz_sub_ui(m, m, 1);
	mpz_tdiv_q(m, m, Unumber::n);
	mpz_mul(m, m, Unumber::mi);
	mpz_mod(m, m, Unumber::n);
}

void Unumber::encrypt(mpz_t c, const mpz_t m)
{
	mpz_t r,gcd;
	mpz_init(r);
	mpz_init(gcd);
	do
	{
		e3_random(r,n);
		mpz_gcd(gcd, r, n);
	} while (mpz_cmp_ui(gcd, 1));

	mpz_powm(c, Unumber::g, m, Unumber::n2);
	mpz_powm(r, r, Unumber::n, Unumber::n2);
	mpz_mul(c, c, r);
	mpz_mod(c, c, Unumber::n2);
}

void Unumber::enc()
{
	//printf("enc in\n");
	mpz_t m,c,r,gcd;
	mpz_init_set(m, z.get_mpz_t());
	mpz_init(c);
	mpz_init(r);
	mpz_init(gcd);
	do
	{
		e3_random(r,n);
		mpz_gcd(gcd, r, n);
	} while (mpz_cmp_ui(gcd, 1));

	mpz_powm(c, Unumber::g, m, Unumber::n2);
	mpz_powm(r, r, Unumber::n, Unumber::n2);
	mpz_mul(c, c, r);
	mpz_mod(c, c, Unumber::n2);
	mpz_set(z.get_mpz_t(), c);
	//printf("enc out\n");
}

void Unumber::setKey(Unumber pri, Unumber pub, Unumber mod, unsigned esize, unsigned dsize)
{
	//printf("Setting key...\n");
	mpz_t mask;
	mpz_init_set_ui(mask, 1);
	mpz_mul_2exp(mask, mask, esize/2);
	mpz_sub_ui(mask, mask, 1);

	mpz_init(Unumber::n);
	mpz_init(Unumber::g);
	mpz_init(Unumber::phi);
	mpz_init(Unumber::mi);

	mpz_and(Unumber::mi, pri.z.get_mpz_t(), mask);
	mpz_tdiv_q_2exp(Unumber::phi, pri.z.get_mpz_t(), esize/2);

	mpz_and(Unumber::g, pub.z.get_mpz_t(), mask);
	mpz_tdiv_q_2exp(Unumber::n, pub.z.get_mpz_t(), esize/2);

	mpz_mul(Unumber::n2, Unumber::n, Unumber::n);

	mpz_init_set_ui(one, 1);
	encrypt(one, one);

	ees = esize;
	eds = dsize;
	//printf("Setting key...done\n");
}

void Unumber::eadd(Unumber param)
{
	mpz_mul(z.get_mpz_t(), z.get_mpz_t(), param.z.get_mpz_t());
	mpz_mod(z.get_mpz_t(), z.get_mpz_t(), Unumber::n2);
}

void Unumber::eradd(Unumber param)
{
/*	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.eradd ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);*/
}


void Unumber::esub(Unumber param)
{
	mpz_t inv;
	mpz_init(inv);
	mpz_invert(inv, param.z.get_mpz_t(), Unumber::n2);
	mpz_mul(z.get_mpz_t(), z.get_mpz_t(), inv);
	mpz_mod(z.get_mpz_t(), z.get_mpz_t(), Unumber::n2);
}

void Unumber::ersub(Unumber param)
{
/*	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.ersub ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);*/
}

void Unumber::exor(Unumber param)
{
	//printf("exor in\n");
	mpz_t n1, n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, z.get_mpz_t());
	decrypt(n2, param.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_xor(n1, n1, n2);
	encrypt(z.get_mpz_t(), n1);
	//printf("exor out\n");
}

void Unumber::eror(Unumber param)
{
	//printf("eror in\n");
	mpz_t n1, n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, z.get_mpz_t());
	decrypt(n2, param.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);

	unsigned shift = mpz_get_ui(n2);

	mpz_t mask;
	mpz_init_set_ui(mask, 1);
	mpz_mul_2exp(mask, mask, shift);
	mpz_sub_ui(mask, mask, 1);
	mpz_and(n2, n1, mask);
	mpz_mul_2exp(n2, n2, eds-shift);

	mpz_tdiv_q_2exp(n1, n1, shift);

	mpz_ior(n1, n1, n2);

	encrypt(z.get_mpz_t(), n1);
	//printf("eror out\n");
}

void Unumber::eand(Unumber param)
{
	//printf("eor in\n");
	mpz_t n1, n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, z.get_mpz_t());
	decrypt(n2, param.z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_and(n1, n1, n2);
	encrypt(z.get_mpz_t(), n1);
	//printf("eor out\n");
}

void Unumber::eor(Unumber param)
{
	//printf("eor in\n");
	mpz_t n1, n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, z.get_mpz_t());
	decrypt(n2, param.z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_ior(n1, n1, n2);
	encrypt(z.get_mpz_t(), n1);
	//printf("eor out\n");
}

void Unumber::emuls(Unumber param)
{
	//printf("emuls in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, z.get_mpz_t());
	decrypt(n2, param.z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_mul(n1, n1, n2);
	mpz_mod(n1, n1, n);
	encrypt(z.get_mpz_t(), n1);
	//printf("emuls out\n");
}

void Unumber::esll(Unumber param)
{
	//printf("esll in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, z.get_mpz_t());
	decrypt(n2, param.z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_mul_2exp(n1, n1, mpz_get_ui(n2));
	mpz_mod(n1, n1, n);
	encrypt(z.get_mpz_t(), n1);
	//printf("esll out\n");
}

void Unumber::esra(Unumber param)
{
	//printf("esra in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, z.get_mpz_t());
	decrypt(n2, param.z.get_mpz_t());
/*
	mpz_t mask;
	mpt_init_set_ui(mask, 1);
	mpz_mul_2exp(mask, mask, eds-1);
	mpz_and(mask, mask, n1);
	unsigned sign = mpz_cmp_ui(mask, 0) != 0;
*/
	unsigned shift = mpz_get_ui(n2);
	mpz_tdiv_q_2exp(n1, n1, shift);

	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_mul_2exp(n1, n1, mpz_get_ui(n2));
	mpz_mod(n1, n1, n);
	encrypt(z.get_mpz_t(), n1);
	//printf("esra out\n");
}

void Unumber::elnot()
{
	//printf("elnot in\n");
	mpz_t n1;
	mpz_init(n1);
	decrypt(n1, z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp_ui(n1, 0) == 0;
	mpz_set_ui(n1, cmp);
	encrypt(z.get_mpz_t(), n1);
	//printf("elnot out\n");
}

void Unumber::einc()
{
	mpz_mul(z.get_mpz_t(), z.get_mpz_t(), one);
	mpz_mod(z.get_mpz_t(), z.get_mpz_t(), n2);
}

void Unumber::edec()
{
	mpz_t inv;
	mpz_init(inv);
	mpz_invert(inv, one, Unumber::n2);
	mpz_mul(z.get_mpz_t(), z.get_mpz_t(), inv);
	mpz_mod(z.get_mpz_t(), z.get_mpz_t(), Unumber::n2);
}

void Unumber::eeq(Unumber param1, Unumber param2)
{
	//printf("eeq in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, param1.z.get_mpz_t());
	decrypt(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) == 0;
	mpz_set_ui(n1, cmp);
	encrypt(z.get_mpz_t(), n1);
	//printf("eeq out\n");
}

void Unumber::ene(Unumber param1, Unumber param2)
{
	//printf("ene in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, param1.z.get_mpz_t());
	decrypt(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) != 0;
	mpz_set_ui(n1, cmp);
	encrypt(z.get_mpz_t(), n1);
	//printf("ene out\n");
}

void Unumber::egts(Unumber param1, Unumber param2)
{
	//printf("egts in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, param1.z.get_mpz_t());
	decrypt(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) > 0;
	mpz_set_ui(n1, cmp);
	encrypt(z.get_mpz_t(), n1);
	//printf("egts out\n");
}

void Unumber::eges(Unumber param1, Unumber param2)
{
	//printf("eges in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, param1.z.get_mpz_t());
	decrypt(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) >= 0;
	mpz_set_ui(n1, cmp);
	encrypt(z.get_mpz_t(), n1);
	//printf("eges out\n");
}

void Unumber::elts(Unumber param1, Unumber param2)
{
	//printf("elts in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, param1.z.get_mpz_t());
	decrypt(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) < 0;
	mpz_set_ui(n1, cmp);
	encrypt(z.get_mpz_t(), n1);
	//printf("elts out\n");
}

void Unumber::eles(Unumber param1, Unumber param2)
{
	//printf("eles in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, param1.z.get_mpz_t());
	decrypt(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) <= 0;
	mpz_set_ui(n1, cmp);
	encrypt(z.get_mpz_t(), n1);
	//printf("eles out\n");
}

void Unumber::ecmov(Unumber param1, Unumber param2)
{
	printf("ecmov in\n");
	mpz_t n1;
	mpz_init(n1);
	decrypt(n1, z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp_ui(n1, 0) == 0;
	if (cmp) mpz_set(z.get_mpz_t(), param1.z.get_mpz_t());
	else  mpz_set(z.get_mpz_t(), param2.z.get_mpz_t());
	printf("ecmov out\n");
}

void Unumber::emacs(Unumber param1, Unumber param2)
{
	//printf("emacs in\n");
	mpz_t n0,n1,n2;
	mpz_init(n0);
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n0, z.get_mpz_t());
	decrypt(n1, param1.z.get_mpz_t());
	decrypt(n2, param2.z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_mul(n1, n1, n2);
	mpz_mod(n1, n1, n);
	mpz_add(n0, n0, n1);
	encrypt(z.get_mpz_t(), n0);
	//printf("emacs out\n");
}

void Unumber::e3_random(mpz_t r, mpz_t limit)
{
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state, rand());
	mpz_init(r);
	mpz_urandomm(r, state, limit);
}

void Unumber::e3_randomp2(mpz_t r, unsigned limit)
{
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state, rand());
	mpz_init(r);
	mpz_urandomb(r, state, limit);
}

void Unumber::add(Unumber param)
{
	mpz_add(z.get_mpz_t(), z.get_mpz_t(), param.z.get_mpz_t());
}


void Unumber::sub(Unumber param)
{
	mpz_sub(z.get_mpz_t(), z.get_mpz_t(), param.z.get_mpz_t());
}

void Unumber::pxor(Unumber param)
{
	mpz_xor(z.get_mpz_t(), z.get_mpz_t(), param.z.get_mpz_t());
}

void Unumber::ror(Unumber param)
{
	//printf("eror in\n");
	mpz_t n1, n2;
	mpz_init_set(n1, z.get_mpz_t());
	mpz_init_set(n2, param.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);

	unsigned shift = mpz_get_ui(n2);

	mpz_t mask;
	mpz_init_set_ui(mask, 1);
	mpz_mul_2exp(mask, mask, shift);
	mpz_sub_ui(mask, mask, 1);
	mpz_and(n2, n1, mask);
	mpz_mul_2exp(n2, n2, eds-shift);

	mpz_tdiv_q_2exp(n1, n1, shift);

	mpz_ior(n1, n1, n2);
	mpz_set(z.get_mpz_t(), n1);
	//printf("eror out\n");
}

void Unumber::pand(Unumber param)
{
	//printf("eor in\n");
	mpz_t n1, n2;
	mpz_init(n1);
	mpz_init(n2);
	mpz_set(n1, z.get_mpz_t());
	mpz_set(n2, param.z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_and(n1, n1, n2);
	mpz_set(z.get_mpz_t(), n1);
	//printf("eor out\n");
}

void Unumber::por(Unumber param)
{
	//printf("eor in\n");
	mpz_t n1, n2;
	mpz_init(n1);
	mpz_init(n2);
	mpz_set(n1, z.get_mpz_t());
	mpz_set(n2, param.z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_ior(n1, n1, n2);
	mpz_set(z.get_mpz_t(), n1);
	//printf("eor out\n");
}

void Unumber::muls(Unumber param)
{
	//printf("emuls in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, z.get_mpz_t());
	decrypt(n2, param.z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_mul(n1, n1, n2);
	mpz_mod(n1, n1, n);
	encrypt(z.get_mpz_t(), n1);
	//printf("emuls out\n");
}

void Unumber::sll(Unumber param)
{
	//printf("esll in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	mpz_set(n1, z.get_mpz_t());
	mpz_set(n2, param.z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_mul_2exp(n1, n1, mpz_get_ui(n2));
	mpz_mod(n1, n1, n);
	mpz_set(z.get_mpz_t(), n1);
	//printf("esll out\n");
}

void Unumber::sra(Unumber param)
{
	//printf("esra in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	mpz_set(n1, z.get_mpz_t());
	mpz_set(n2, param.z.get_mpz_t());
/*
	mpz_t mask;
	mpt_init_set_ui(mask, 1);
	mpz_mul_2exp(mask, mask, eds-1);
	mpz_and(mask, mask, n1);
	unsigned sign = mpz_cmp_ui(mask, 0) != 0;
*/
	unsigned shift = mpz_get_ui(n2);
	mpz_tdiv_q_2exp(n1, n1, shift);

	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_mul_2exp(n1, n1, mpz_get_ui(n2));
	mpz_mod(n1, n1, n);
	mpz_set(z.get_mpz_t(), n1);
	//printf("esra out\n");
}

void Unumber::lnot()
{
	//printf("elnot in\n");
	mpz_t n1;
	mpz_init(n1);
	mpz_set(n1, z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp_ui(n1, 0) == 0;
	mpz_set_ui(n1, cmp);
	mpz_set(z.get_mpz_t(), n1);
	//printf("elnot out\n");
}

void Unumber::inc()
{
	mpz_add_ui(z.get_mpz_t(), z.get_mpz_t(), 1);
}

void Unumber::dec()
{
	mpz_sub_ui(z.get_mpz_t(), z.get_mpz_t(), 1);
}

void Unumber::eq(Unumber param1, Unumber param2)
{
	//printf("eeq in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	decrypt(n1, param1.z.get_mpz_t());
	decrypt(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) == 0;
	mpz_set_ui(n1, cmp);
	encrypt(z.get_mpz_t(), n1);
	//printf("eeq out\n");
}

void Unumber::ne(Unumber param1, Unumber param2)
{
	//printf("ene in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	mpz_set(n1, param1.z.get_mpz_t());
	mpz_set(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) != 0;
	mpz_set_ui(n1, cmp);
	mpz_set(z.get_mpz_t(), n1);
	//printf("ene out\n");
}

void Unumber::gts(Unumber param1, Unumber param2)
{
	//printf("egts in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	mpz_set(n1, param1.z.get_mpz_t());
	mpz_set(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) > 0;
	mpz_set_ui(n1, cmp);
	mpz_set(z.get_mpz_t(), n1);
	//printf("egts out\n");
}

void Unumber::ges(Unumber param1, Unumber param2)
{
	//printf("eges in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	mpz_set(n1, param1.z.get_mpz_t());
	mpz_set(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) >= 0;
	mpz_set_ui(n1, cmp);
	mpz_set(z.get_mpz_t(), n1);
	//printf("eges out\n");
}

void Unumber::lts(Unumber param1, Unumber param2)
{
	//printf("elts in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	mpz_set(n1, param1.z.get_mpz_t());
	mpz_set(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) < 0;
	mpz_set_ui(n1, cmp);
	mpz_set(z.get_mpz_t(), n1);
	//printf("elts out\n");
}

void Unumber::les(Unumber param1, Unumber param2)
{
	//printf("eles in\n");
	mpz_t n1,n2;
	mpz_init(n1);
	mpz_init(n2);
	mpz_set(n1, param1.z.get_mpz_t());
	mpz_set(n2, param2.z.get_mpz_t());
	////gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp(n1, n2) <= 0;
	mpz_set_ui(n1, cmp);
	mpz_set(z.get_mpz_t(), n1);
	//printf("eles out\n");
}

void Unumber::cmov(Unumber param1, Unumber param2)
{
	//printf("ecmov in\n");
	mpz_t n1;
	mpz_init(n1);
	mpz_set(n1, z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	unsigned cmp = mpz_cmp_ui(n1, 0) == 0;
	if (cmp) mpz_set(z.get_mpz_t(), param1.z.get_mpz_t());
	//else  mpz_set(z.get_mpz_t(), param2.z.get_mpz_t());
	printf("ecmov out\n");
}

void Unumber::macs(Unumber param1, Unumber param2)
{
	//printf("emacs in\n");
	mpz_t n0,n1,n2;
	mpz_init(n0);
	mpz_init(n1);
	mpz_init(n2);
	mpz_set(n0, z.get_mpz_t());
	mpz_set(n1, param1.z.get_mpz_t());
	mpz_set(n2, param2.z.get_mpz_t());
	//gmp_printf("%Zd\t%Zd\n", n1, n2);
	mpz_mul(n1, n1, n2);
	mpz_mod(n1, n1, n);
	mpz_add(n0, n0, n1);
	mpz_set(z.get_mpz_t(), n0);
	//printf("emacs out\n");
}

void Unumber::randomp2(unsigned limit)
{
	mpz_t r;
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state, rand());
	mpz_init(r);
	mpz_urandomb(r, state, limit);
	mpz_set(z.get_mpz_t(), r);
}

void Unumber::setControl(unsigned control)
{
	unsigned esize = control;
	unsigned dsize = control;
	unsigned ctrl = 0, address = 12 << 11;

	esize /= 512;
	while (esize >>= 1) ctrl++;
	//ctrl--;
	ctrl <<= 8;

	dsize /= 32;
	while (dsize >>= 1) ctrl++;
	//ctrl--;
	ctrl <<= 8;
/*
	printf("address: %x\n", address);
	printf("ctrl: %x\n", ctrl);
*/
//	__asm__ ("l.mtspr %0,%1,0" : : "r"(address), "r"(ctrl));
}
