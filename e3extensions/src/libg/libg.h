/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

/*******************************************
* Note: this G function is not secure      *
        it is merely functional            *
        use it only for testing purpose    *
********************************************/

#ifndef __LIBG_H__
#define __LIBG_H__

#ifdef __cplusplus
extern "C" {
#endif

Unumber congruence(Unumber, const Unumber &);
Unumber encrypt(const Unumber &);
bool leq(const Unumber);
Unumber libg(Unumber, Unumber);
Unumber reencrypt(const Unumber &);
//#ifndef STATIC_LIBG
void loadCryptosystemParams();
//#endif

#ifdef __cplusplus
}
#endif

#endif
