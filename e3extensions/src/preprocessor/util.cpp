/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#include "util.h"

/* Split string into vector elements */
const vector<string> explode(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

/* find the index of a element in a vector */
int indexOf(vector<string> v, const string & elem)
{
	for (int i = 0; (unsigned) i < v.size(); i++)
	{
		if (elem.compare(v[i]) == 0) return i;
	}

	return -1;
}

/* Return true if the character at pos is inside of a block comment */
bool isBlockComment(const string & code, const int pos)
{
	int blockCommentStartBefore = code.rfind("/*", pos);
	int blockCommentEndBefore = code.rfind("*/", pos);
	if (blockCommentStartBefore <= blockCommentEndBefore) return false;
	
	return true;
}

/* Return true if the character at pos is inside of a comment */
bool isComment(const string & code, const int pos)
{
	return (isLineComment(code, pos) || isBlockComment(code, pos));
}

/* Return true if the character at pos is inside of a line comment */
bool isLineComment(const string & code, const int pos)
{
	int newLineBefore = code.rfind("\n", pos) + 1;
	int newLineAfter = code.find("\n", pos);

	string line;
	if (newLineAfter == -1) code.substr(newLineBefore);
	else line = code.substr(newLineBefore, newLineAfter - newLineBefore);
	int lineComment = line.find("//");
	
	return ((lineComment != -1) && (lineComment < newLineBefore));
}

/* Check if a string contains only numbers */
bool isNumber(string & s)
{
	for (unsigned i = 0; i < s.length(); i++)
	{
		if ((s[i] < '0') || (s[i] > '9')) return false;
	}

	return true;
}

/* Remove the leading and trailing spaces */
void trim(string & s)
{
	size_t p = s.find_first_not_of(" \t\n");
	s.erase(0, p);

	p = s.find_last_not_of(" \t");
	if (string::npos != p)
		s.erase(p+1);
}

/* Convert a vector to a string (elements are separated by comma */
string vectorToString(vector<string> v)
{
	string s = "";

	if (!v.empty())
	{
		for (unsigned i = 0; i < v.size()-1; i++)
		{
			s.append("\"" + v[i] + "\",");
		}
		s.append("\"" + v[v.size()-1] + "\"");
	}

	return s;
}

