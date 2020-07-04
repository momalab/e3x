#include <iostream>
#include <istream>
#include "unumberzx.h"

//#if HWACC == 4096
	#include "unumberzx4096asm.h"
/*
#elif HWACC == 2048
	#include "unumberzx2048asm.h"
#elif HWACC == 1024
	#include "unumberzx1024asm.h"
#elif HWACC == 512
	#include "unumberzx512asm.h"
#else
	#include "unumberzx2048asm.h"
#endif
*/

const bool NP_DBG = false;

Unumber Unumber::MOD_VALUE = 0;

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

void Unumber::operator*=(const Unumber & n) { z *= n.z; /*stats_operatorMul++;*/ }
void Unumber::operator+=(const Unumber & n) { z += n.z; pos(); /*stats_operatorAdd++;*/ }
void Unumber::operator-=(const Unumber & n) { z -= n.z; neg(); /*stats_operatorSub++;*/ }
void Unumber::operator%=(const Unumber & n) { z %= n.z;/* stats_operatorMod++;*/ }
void Unumber::operator/=(const Unumber & n) { z /= n.z; /*stats_operatorDiv++;*/ }

Unumber & Unumber::operator++() { /*stats_operatorInc++;*/ z += 1; return *this; }
Unumber & Unumber::operator--() {/* stats_operatorDec++;*/ z -= 1; return *this; }

bool Unumber::iszero() const { /*stats_iszero++;*/ return z == 0; }

string Unumber::str(unsigned base) const { return z.get_str(base); }

unsigned long long Unumber::to_ull() const { return z.get_ui(); }

void Unumber::operator<<=(int b) { mpz_mul_2exp (z.get_mpz_t(), z.get_mpz_t(), b); /*stats_operatorShiftLeft++;*/ }
void Unumber::operator>>=(int b) { mpz_div_2exp (z.get_mpz_t(), z.get_mpz_t(), b); /*stats_operatorShiftRight++;*/ }

bool operator<(const Unumber & n1, const Unumber & n2) { /*stats_operatorLess++;*/ return n1.z < n2.z; }
bool operator==(const Unumber & n1, const Unumber & n2) { /*stats_operatorEqual++;*/ return n1.z == n2.z; }

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
/*stats_div++;*/
    Unumber r;
    mpz_fdiv_qr (q.z.get_mpz_t(), r.z.get_mpz_t(), z.get_mpz_t(), d.z.get_mpz_t());
    return r;
}

void Unumber::divABRQ(const Unumber & d, Unumber * r, Unumber * q) const
{
/*stats_divABRQ++;*/
    Unumber m;

    if (q)
        mpz_fdiv_qr (q->z.get_mpz_t(), m.z.get_mpz_t(), z.get_mpz_t(), d.z.get_mpz_t());
    else
        mpz_fdiv_r (m.z.get_mpz_t(), z.get_mpz_t(), d.z.get_mpz_t());

    if (r) *r = m;
}

Unumber Unumber::mul(const Unumber & b, const Unumber & m) const
{
/*stats_mul++;*/
//std::cout << "mul\n";
	Unumber r;
/*
	mpz_mul(r.z.get_mpz_t(), z.get_mpz_t(), b.z.get_mpz_t());
	mpz_mod(r.z.get_mpz_t(), r.z.get_mpz_t(), m.z.get_mpz_t());
*/

	//std::cout << "Unumber::mul in\n";

	if (!mpz_cmp_ui(z.get_mpz_t(), 0) || !mpz_cmp_ui(b.z.get_mpz_t(), 0)) mpz_set_ui(r.z.get_mpz_t(), 0);
	else
	{
		unsigned length = HW_NUMWORDS;
		size_t *countp;
		unsigned order = 1;
		unsigned endianess = 1;
		unsigned nails = 0;
		unsigned mA[length], mB[length], mC[length], mD[length];
		unsigned size = length * sizeof(unsigned);

		mpz_export(mA, countp, order, size, endianess, nails, z.get_mpz_t());
		mpz_export(mB, countp, order, size, endianess, nails, b.z.get_mpz_t());

		if (mpz_cmp_ui(m.z.get_mpz_t(), 0)) mpz_export(mC, countp, order, size, endianess, nails, m.z.get_mpz_t());
		else for (unsigned i = 0; i < length; i++) mC[i] = 0;
/*
		mter_e1(mA);
		mter_e2(mB);
		mter_e3(mC);

		//hw_modmul();

		mfer_e0(mD);
*/
		mpz_import(r.z.get_mpz_t(), length, order, sizeof(unsigned), endianess, nails, mD);
	}

	//std::cout << "Unumber::mul out\n";

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
/*stats_pow++;*/
//std::cout << "pow\n";
//	mpz_powm(z.get_mpz_t(), z.get_mpz_t(), e.z.get_mpz_t(), mod.z.get_mpz_t());
	//std::cout << "Unumber::pow in\n";

	unsigned length = HW_NUMWORDS;
	size_t *countp;
	unsigned order = 1;
	unsigned endianess = 1;
	unsigned nails = 0;
	unsigned mA[length], mB[length], mC[length], mD[length];
	unsigned size = length * sizeof(unsigned);

	//gmp_printf("mA: %Zx\tmB: %Zx\tmC: %Zx\n", z.get_mpz_t(), e.z.get_mpz_t(), mod.z.get_mpz_t());

	if (mpz_cmp_ui(z.get_mpz_t(), 0)) mpz_export(mA, countp, order, size, endianess, nails, z.get_mpz_t());
	else for (unsigned i = 0; i < length; i++) mA[i] = 0;

	if (mpz_cmp_ui(e.z.get_mpz_t(), 0)) mpz_export(mB, countp, order, size, endianess, nails, e.z.get_mpz_t());
	else for (unsigned i = 0; i < length; i++) mB[i] = 0;

	if (mpz_cmp_ui(mod.z.get_mpz_t(), 0)) mpz_export(mC, countp, order, size, endianess, nails, mod.z.get_mpz_t());
	else for (unsigned i = 0; i < length; i++) mC[i] = 0;
/*
	mter_e1(mA);
	mter_e2(mB);
	mter_e3(mC);

	//hw_modexp();

	mfer_e0(mD);
*/
	mpz_import(z.get_mpz_t(), length, order, sizeof(unsigned), endianess, nails, mD);

	//std::cout << "Unumber::pow out\n";
}

void Unumber::swap(Unumber & n) { /*stats_swap++;*/ mpz_class t = z; z=n.z; n.z=t; }

void Unumber::toArray(unsigned arr[])
{
	unsigned length = HW_NUMWORDS;
	size_t *countp;
	unsigned size = length * sizeof(unsigned);
	if (mpz_cmp_ui(z.get_mpz_t(), 0)) mpz_export(arr, countp, ORDER, size, ENDIANESS, NAILS, z.get_mpz_t());
	else for (unsigned i = 0; i < length; i++) arr[i] = 0;
}

void Unumber::fromArray(unsigned arr[])
{
	unsigned length = HW_NUMWORDS;
	mpz_import(z.get_mpz_t(), length, ORDER, sizeof(unsigned), ENDIANESS, NAILS, arr);
}

void Unumber::exportArray(unsigned arr[], unsigned length, Unumber u)
{
	size_t *countp;
	unsigned size = length * sizeof(unsigned);
	if (mpz_cmp_ui(u.z.get_mpz_t(), 0)) mpz_export(arr, countp, ORDER, size, ENDIANESS, NAILS, u.z.get_mpz_t());
	else for (unsigned i = 0; i < length; i++) arr[i] = 0;
}

Unumber Unumber::importArray(unsigned arr[], unsigned length)
{
	Unumber r;
	mpz_import(r.z.get_mpz_t(), length, ORDER, sizeof(unsigned), ENDIANESS, NAILS, arr);
	return r;
}

/*
void Unumber::prita()
{
	std::cout << "---\n";

	std::cout << "stats_operatorAdd: " << stats_operatorAdd << "\n";
	std::cout << "stats_operatorSub: " << stats_operatorSub << "\n";
	std::cout << "stats_operatorMul: " << stats_operatorMul << "\n";
	std::cout << "stats_operatorDiv: " << stats_operatorDiv << "\n";
	std::cout << "stats_operatorMod: " << stats_operatorMod << "\n";
	std::cout << "stats_operatorShiftLeft: " << stats_operatorShiftLeft << "\n";
	std::cout << "stats_operatorShiftRight: " << stats_operatorShiftRight << "\n";
	std::cout << "stats_operatorLess: " << stats_operatorLess << "\n";
	std::cout << "stats_operatorGreater: " << stats_operatorGreater << "\n";
	std::cout << "stats_operatorEqual: " << stats_operatorEqual << "\n";
	std::cout << "stats_operatorInc: " << stats_operatorInc << "\n";
	std::cout << "stats_operatorDec: " << stats_operatorDec << "\n";
	std::cout << "stats_iszero: " << stats_iszero << "\n";
	std::cout << "stats_swap: " << stats_swap << "\n";
	std::cout << "stats_div: " << stats_div << "\n";
	std::cout << "stats_divABRQ: " << stats_divABRQ << "\n";
	std::cout << "stats_mul: " << stats_mul << "\n";
	std::cout << "stats_pow: " << stats_pow << "\n";

	std::cout << "---\n";
}
*/


void Unumber::setKey(Unumber pri, Unumber pub, Unumber mod, unsigned esize, unsigned dsize)
{
	unsigned ctrl = 0, address = 12 << 11;

	esize /= 512;
	while (esize >>= 1) ctrl++;
	ctrl <<= 8;

	dsize /= 32;
	while (dsize >>= 1) ctrl++;
	ctrl <<= 8;

	__asm__ ("l.mtspr %0,%1,0" : : "r"(address), "r"(ctrl));

	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mC[HW_NUMWORDS];
	pub.toArray(mA);
	mod.toArray(mB);
	pri.toArray(mC);

	mter_e1(mA);
	mter_e2(mB);
	mter_e3(mC);

	__asm__(
		"le.mtspr pub,ze1\n\t"
		"le.mtspr mod,ze2\n\t"
		"le.mtspr pri,ze3"
	);
}

void Unumber::eadd(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.eadd ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::eradd(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.eradd ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}


void Unumber::esub(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.esub ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::ersub(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.ersub ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::exor(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.exor ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::eror(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.eror ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::eor(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.eor ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::emuls(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.emuls ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::esll(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.esll ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::esra(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.esra ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::elnot()
{
	unsigned mA[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	mter_e1(mA);
	__asm__("le.elnot ze0,ze1");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::einc()
{
	unsigned mD[HW_NUMWORDS];
	this->toArray(mD);
	mter_e0(mD);
	__asm__("le.einc ze0");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::edec()
{
	unsigned mD[HW_NUMWORDS];
	this->toArray(mD);
	mter_e0(mD);
	__asm__("le.edec ze0");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::eeq(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.eeq ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::ene(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.ene ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::egts(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.egts ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::eges(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.eges ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::elts(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.elts ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::eles(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.eles ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::ecmov(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mD);
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e0(mD);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.ecmov ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::emacs(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mD);
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e0(mD);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.emacs ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::enc()
{
	unsigned mA[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	mter_e1(mA);
	__asm__("le.enc ze0,ze1");
	mfer_e0(mD);
	this->fromArray(mD);
}


/**********************/


void Unumber::add(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.add ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::sub(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.sub ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::pxor(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.xor ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::ror(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.ror ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::por(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.or ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::muls(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.muls ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::sll(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.sll ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::sra(Unumber param)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	param.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.sra ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::lnot()
{
	unsigned mA[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mA);
	mter_e1(mA);
	__asm__("le.lnot ze0,ze1");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::inc()
{
	unsigned mD[HW_NUMWORDS];
	this->toArray(mD);
	mter_e0(mD);
	__asm__("le.inc ze0");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::dec()
{
	unsigned mD[HW_NUMWORDS];
	this->toArray(mD);
	mter_e0(mD);
	__asm__("le.dec ze0");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::eq(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.eq ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::ne(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.ne ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::gts(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.gts ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::ges(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.ges ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::lts(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.lts ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::les(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.les ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::cmov(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mD);
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e0(mD);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.cmov ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
}

void Unumber::macs(Unumber param1, Unumber param2)
{
	unsigned mA[HW_NUMWORDS], mB[HW_NUMWORDS], mD[HW_NUMWORDS];
	this->toArray(mD);
	param1.toArray(mA);
	param2.toArray(mB);
	mter_e0(mD);
	mter_e1(mA);
	mter_e2(mB);
	__asm__("le.macs ze0,ze1,ze2");
	mfer_e0(mD);
	this->fromArray(mD);
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
	//gmp_printf("%Zd %u\n", r, limit);
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
	__asm__ ("l.mtspr %0,%1,0" : : "r"(address), "r"(ctrl));
}
