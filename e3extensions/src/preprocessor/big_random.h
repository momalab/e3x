/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#ifndef __BIG_RANDOM_H__
#define __BIG_RANDOM_H__

#include "../unumber/unumberg.h"

#ifdef ARCH64
	#define WORD_SIZE 64
#else
	#define WORD_SIZE 32
#endif

Unumber invertibleRandom(const Unumber &, const Unumber &);
bool millerRabin(const Unumber &, int);
Unumber oddRandom(const Unumber &, const Unumber &);
Unumber prime(Unumber from, Unumber to);
Unumber random(const Unumber &, const Unumber &);

#endif

