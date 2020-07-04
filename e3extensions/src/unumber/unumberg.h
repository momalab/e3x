extern const char * BIGNUM_NAME;

#include "cunum_def_4096.hh"

#if defined(GMP) && defined(HWACC)
#include "unumberzx.h"

#elif defined(GMP)
#include "unumberz.h"

#elif defined(HWACC)
#include "unumberx.h"

#else
#include "unumber.h"

#endif

#include "ma_invert_m.h"

/*
#ifndef GMP

#include "cunum_def_4096.hh"
#include "unumber.h"

#else

#include "cunum_def_4096.hh"
#include "unumberz.h"

#endif

#include "ma_invert_m.h"
*/

