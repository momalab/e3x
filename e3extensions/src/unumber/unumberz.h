#ifndef UNUMBEZ_H__
#define UNUMBEZ_H__

#include <sstream>
#include <string>
#include <ostream>
#include <istream>
#include <cctype>
#include <cstring>

#include <stddef.h>
#include <gmpxx.h>

using std::string;

class Unumber
{
        mpz_class z;
        void neg();
        void pos();

        static const int MOD_POWER = 4096;
        static Unumber MOD_VALUE;
        static void init_mod_value();

    public:
	static mpz_t n, n2, g, phi, mi, one;
	static unsigned ees, eds;
        Unumber(unsigned long long x);
        Unumber();

         enum StringType { Binary, Decimal, Hexadecimal };
        Unumber(const string & s, StringType st);
	Unumber(const string & s, unsigned int base=0);
	Unumber(const Unumber & n);

	void init(const char *, unsigned);
        void init10(const char * s);
        void initBin(const string & s);

        void operator-=(const Unumber & n);
        void operator+=(const Unumber & n);
        void operator*=(const Unumber & n);
        void operator%=(const Unumber & n);
        void operator/=(const Unumber & n);

        void setbit1(int b);
        unsigned getbit(int b) const;

        void pow(Unumber e, const Unumber & mod);

        Unumber div(const Unumber & d, Unumber & q) const;

        Unumber mul(const Unumber & b, const Unumber & m) const;

        void divABRQ(const Unumber & d, Unumber * r, Unumber * q) const;

        bool iszero() const;

        Unumber & operator++();
        Unumber & operator--();

        void operator<<=(int b);
        void operator>>=(int b);

        friend Unumber operator-(const Unumber & n1, const Unumber & n2)
        { Unumber r(n1); r -= n2; return r; }

        friend Unumber operator*(const Unumber & n1, const Unumber & n2)
        { Unumber r(n1); r *= n2; return r; }

        friend Unumber operator+(const Unumber & n1, const Unumber & n2)
        { Unumber r(n1); r += n2; return r; }

        friend Unumber operator%(const Unumber & n1, const Unumber & n2)
        { Unumber r(n1); r %= n2; return r; }

        friend Unumber operator/(const Unumber & n1, const Unumber & n2)
        { Unumber r(n1); r /= n2; return r; }

        friend bool operator<(const Unumber & n1, const Unumber & n2);

	friend bool operator<=(const Unumber & n1, const Unumber & n2)
	{ return ((n1 < n2) || (n1 == n2)); }

        friend bool operator>(const Unumber & n1, const Unumber & n2) { return n2 < n1; }

	friend bool operator>=(const Unumber & n1, const Unumber & n2)
	{ return ((n1 > n2) || (n1 == n2)); }

        friend bool operator!=(const Unumber & n1, const Unumber & n2)
        { return !(n1 == n2); }

        friend bool operator==(const Unumber & n1, const Unumber & n2)
        { return n1.z == n2.z; }

        void swap(Unumber & n) { mpz_class t = z; z=n.z; n.z=t; }

        string str(unsigned base=10) const;
        unsigned long long to_ull() const;

        friend std::ostream & operator<<(std::ostream & os, const Unumber & n)
        { return (os << n.str()); }

        friend std::istream & operator>>(std::istream & os, Unumber & n);

        string raw(unsigned sz) const;

	static void setKey(Unumber, Unumber, Unumber, unsigned, unsigned);
	static void setControl(unsigned);

	void eadd(Unumber);
	void esub(Unumber);
	void eradd(Unumber);
	void ersub(Unumber);
	void exor(Unumber);
	void eror(Unumber);
    void eand(Unumber);
	void eor(Unumber);
	void einc();
	void edec();
	void esll(Unumber);
	void esra(Unumber);
	void emuls(Unumber);
	void elnot();
	void enc();
	void eeq(Unumber, Unumber);
	void ene(Unumber, Unumber);
	void egts(Unumber, Unumber);
	void eges(Unumber, Unumber);
	void elts(Unumber, Unumber);
	void eles(Unumber, Unumber);
	void ecmov(Unumber, Unumber);
	void emacs(Unumber, Unumber);

	void add(Unumber);
	void sub(Unumber);
	void radd(Unumber);
	void rsub(Unumber);
	void pxor(Unumber);
	void ror(Unumber);
	void por(Unumber);
    void pand(Unumber);
	void inc();
	void dec();
	void sll(Unumber);
	void sra(Unumber);
	void muls(Unumber);
	void lnot();
	void eq(Unumber, Unumber);
	void ne(Unumber, Unumber);
	void gts(Unumber, Unumber);
	void ges(Unumber, Unumber);
	void lts(Unumber, Unumber);
	void les(Unumber, Unumber);
	void cmov(Unumber, Unumber);
	void macs(Unumber, Unumber);
	void randomp2(unsigned);

	private:
	static void decrypt(mpz_t, const mpz_t);
	static void encrypt(mpz_t, const mpz_t);
	static void e3_random(mpz_t, mpz_t);
	static void e3_randomp2(mpz_t, unsigned);
};


inline Unumber operator>>(Unumber a, unsigned b) { a >>= b; return a; }
inline Unumber operator<<(Unumber a, unsigned b) { a <<= b; return a; }

#endif
