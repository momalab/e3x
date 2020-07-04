//#include "stats.h"

#ifndef GMP

const char * BIGNUM_NAME = "UNUM";

#else // begin GMP

#ifndef HWACC

#include "cunum_def_4096.hh"
#include "unumberz.cpp"

#else

#include "cunum_def_4096.hh"
#include "unumberzx.cpp"

#endif

#if defined __SIZEOF_SIZE_T__

#if __SIZEOF_SIZE_T__ == 8
const char * BIGNUM_NAME = "GMP-64b";
#else
const char * BIGNUM_NAME = "GMP-32b";
#endif // 64

#else
const char * BIGNUM_NAME = "GMP";
#endif

#endif // end GMP


