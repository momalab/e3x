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

#define ORDER 1
#define ENDIANESS 1
#define NAILS 0

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

        friend bool operator==(const Unumber & n1, const Unumber & n2);

        void swap(Unumber & n);

        string str(unsigned base=10) const;
        unsigned long long to_ull() const;

        friend std::ostream & operator<<(std::ostream & os, const Unumber & n)
        { return (os << n.str()); }

        friend std::istream & operator>>(std::istream & os, Unumber & n);

        string raw(unsigned sz) const;

	//void prita();

	/* Assembly support */
	static unsigned HW_NUMWORDS;

	void toArray(unsigned[]);
	void fromArray(unsigned[]);

	static void exportArray(unsigned[], unsigned, Unumber);
	static Unumber importArray(unsigned[], unsigned);

	static void sw_e0(unsigned[]);
	static void sw_e1(unsigned[]);
	static void sw_e2(unsigned[]);
	static void sw_e3(unsigned[]);
	static void lw_e0(unsigned[]);
	static void lw_e1(unsigned[]);
	static void lw_e2(unsigned[]);
	static void lw_e3(unsigned[]);

	static void mfer_e0(unsigned[]);
	static void mfer_e1(unsigned[]);
	static void mfer_e2(unsigned[]);
	static void mfer_e3(unsigned[]);
    static void mfer_e4(unsigned[]);
    static void mfer_e5(unsigned[]);
    static void mfer_e6(unsigned[]);
    static void mfer_e7(unsigned[]);
    static void mfer_e8(unsigned[]);
    static void mfer_e9(unsigned[]);
    static void mfer_e10(unsigned[]);
    static void mfer_e11(unsigned[]);
    static void mfer_e12(unsigned[]);
    static void mfer_e13(unsigned[]);
    static void mfer_e14(unsigned[]);
    static void mfer_e15(unsigned[]);
	static void mter_e0(unsigned[]);
	static void mter_e1(unsigned[]);
	static void mter_e2(unsigned[]);
	static void mter_e3(unsigned[]);
    static void mter_e4(unsigned[]);
    static void mter_e5(unsigned[]);
    static void mter_e6(unsigned[]);
    static void mter_e7(unsigned[]);
    static void mter_e8(unsigned[]);
    static void mter_e9(unsigned[]);
    static void mter_e10(unsigned[]);
    static void mter_e11(unsigned[]);
    static void mter_e12(unsigned[]);
    static void mter_e13(unsigned[]);
    static void mter_e14(unsigned[]);
    static void mter_e15(unsigned[]);
/*
	static void hw_modmul();
	static void hw_modexp();

	static void hw_gcd();
	static void hw_inv();

	static void hw_gfun();*/
	static void setKey(Unumber, Unumber, Unumber, unsigned, unsigned);
	static void setControl(unsigned);

	void eadd(Unumber);
	void esub(Unumber);
	void eradd(Unumber);
	void ersub(Unumber);
	void exor(Unumber);
	void eror(Unumber);
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
    void pand(Unumber);
	void por(Unumber);
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
};


inline Unumber operator>>(Unumber a, unsigned b) { a >>= b; return a; }
inline Unumber operator<<(Unumber a, unsigned b) { a <<= b; return a; }

#endif
