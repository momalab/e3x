/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#ifndef __SENSITIVE_INFORMATION_H__
#define __SENSITIVE_INFORMATION_H__

#include <vector>
#include "../unumber/unumberg.h"

using namespace std;

class SensitiveInformation
{
    /* Private variables */
    private:
	Unumber p, q, phi, phim1;
	Unumber k, km1, g, rndN;
	Unumber p1Nk1N;
	Unumber Nm1;
	Unumber rnd;
	Unumber n, n2;
	
	Unumber unTwoToBeta, twoToBeta;	
	Unumber xp1, xp2;
	Unumber a2, b2;
	unsigned beta, high_bit_posN, high_bit_posN2;

	vector<string> halfTable;

    /* Public variables */
	Unumber sneak;

    /* Constructors */
    public:
	SensitiveInformation() {}
	SensitiveInformation(const string &, const string &, const string &);
	SensitiveInformation(const string &, const string &, const string &, const string &);
	SensitiveInformation(const string &, const string &, const string &, const string &, unsigned);
	SensitiveInformation(const Unumber, const Unumber, const Unumber);
	SensitiveInformation(const Unumber, const Unumber, const Unumber, const Unumber);
	SensitiveInformation(const Unumber, const Unumber, const Unumber, const Unumber, unsigned);
	SensitiveInformation(unsigned long long, unsigned long long, unsigned long long);
	SensitiveInformation(unsigned long long, unsigned long long, unsigned long long, unsigned long long);

    /* Private functions */
    private:
	Unumber congruence(Unumber x, const Unumber & n);
	void init();
	void setB2Beta(unsigned);

    /* Public functions */
    public:
	void calcHalfTable();
	Unumber decrypt(Unumber, Unumber *);
	Unumber encrypt(Unumber, Unumber);
	Unumber encrypt(Unumber);
        Unumber access_g() const { return g; }
        Unumber access_Nm1() const { return Nm1; }
        Unumber access_p1Nk1N() const { return p1Nk1N; }
        Unumber access_phi() const { return phi; }
        Unumber fkf() const;
	unsigned getBeta() const;
	vector<string> getHalfTable() const;
	unsigned getHighBitPosN() const;
	Unumber getK() const;	
	Unumber getN() const;
	Unumber getN2() const;
	Unumber getP() const;
	Unumber getQ() const;
	Unumber getTwoToBeta() const;
	Unumber getXp1() const;
	Unumber getXp2() const;
        bool isrnd() const { return !rnd.iszero(); }
	bool leq(const Unumber) const;
	void setBeta(unsigned);
};

#endif

