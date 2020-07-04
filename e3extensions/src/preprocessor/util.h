/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <vector>

using namespace std;

const vector<string> explode(const string &, const char &);
int indexOf(vector<string>, const string &);
bool isBlockComment(const string &, const int);
bool isComment(const string &, const int);
bool isLineComment(const string &, const int);
bool isNumber(string &);
void trim(string &);
string vectorToString(vector<string>);

#endif

