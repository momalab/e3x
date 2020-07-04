/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#include "big_random.h"
#include <fstream>
#include <iostream>
#include <regex>
#include "sensitive_information.h"
#include <vector>
#include "../unumber/unumberg.h"
#include "util.h"

using namespace std;

#define NUMBER_OF_CS_PARAMETERS 6
#define NUMBER_OF_SI_PARAMETERS 2

//#define PRIME_FROM "11"
//#define PRIME_TO "1000"
/*
#ifndef KEY_SIZE
	#define KEY_SIZE 1024
#endif

#define PRIME_MAX_EXP KEY_SIZE / 2
#define PRIME_MIN_EXP PRIME_MIN_EXP - 1 */

int keySize = 1024;
int primeMaxExp = keySize / 2;
int primeMinExp = primeMaxExp - 1;
unsigned paramBeta = 0;
vector<string> csList;
vector<SensitiveInformation> sinfoList;
SensitiveInformation sinfo;

string calcNewParamsCS(string);
string calcNewParamsSI(string);
int findClosingBracket(const string &, int);
string findObjectNameBefore(const string &, int);
bool isSecureIntPrecompilerTag(const string &);
bool isValidPQ(const string &);
SensitiveInformation mountSensitiveInformation(string &, unsigned);

/* Transform Cryptosystem values, then encrypt SecureInt values */
int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		cout << "Invalid arguments.\n";
		return 1;
	}

	string filename = argv[1];
	string filenameOut = argv[2];

	if (argc >= 4)
	{
		keySize = (int) (Unumber(argv[3]).to_ull());
		primeMaxExp = keySize / 2;
		primeMinExp = primeMaxExp - 1;
		
	}

	if (argc >= 5)
	{
		paramBeta = (unsigned) (Unumber(argv[4]).to_ull());
	}

	int lastSlash = filename.find_last_of("/\\");
	string filenameCS = filename.substr(0,lastSlash+1) + "CS.txt";
	
	ofstream out;
	out.open(filenameCS, ofstream::out);

	ifstream in;
	stringstream buffer;

	in.open(filename, ifstream::in);
	buffer << in.rdbuf();
	in.close();

	std::string code = buffer.str();

	// Cryptosystem
	cout << "\nCRYPTOSYSTEMs:\n";
	for (int csd = 0; (csd = code.find("Cryptosystem",csd)) != -1; csd++)
	{
		if (!isComment(code,csd))
		{
			int semicolon = code.find(";", csd);
			for (int csi; ((csi = code.find("(", csd)) != -1) && (csi < semicolon);)
			{
				int csf = findClosingBracket(code, csi+1);
				string line = code.substr(csd, csf-csd+1);
				//cout << "CSD: " << csd << "\tCSI: " << csi << "\tSC: " << semicolon << "\tCSF: " << csf << "\tline: " << line << "\tsubstr: " << code.substr(1733, 4) << "\n";
				string objName = code.substr(csd, csi-csd);
				int cso = objName.find_first_of(" \t");
				if (cso > 0) objName = objName.substr(cso);
				trim(objName);
				if (!objName.compare("Cryptosystem")) objName = findObjectNameBefore(code, csd);

				csi++;
				string params = code.substr(csi, csf-csi);
				string newParams = calcNewParamsCS(params);
				code = code.replace(csi, csf-csi, newParams);
				cout << "Object name: " << (objName.empty() ? "(no name)" : objName) << "\nParameters: " << newParams << "\n";
				semicolon = code.find(";", csd);
				csd = csi + newParams.length();

				if (params.compare(newParams))
				{
					if (!objName.empty())
					{
						csList.push_back(objName);
						sinfoList.push_back(sinfo);
						out << objName << ";" << sinfo.getP().str() << ";" << sinfo.getQ().str() << ";" << sinfo.getK().str() << ";" << sinfo.getBeta() << ";" << sinfo.fkf().str() << ";" << sinfo.access_g().str() << ";" << sinfo.getN().str() << ";" << sinfo.getXp1().str() << ";" << sinfo.getXp2().str() << ";" << sinfo.encrypt(Unumber(0)).str() << ";" << sinfo.encrypt(Unumber(1)).str() << "\n";
					}
					Unumber f = sinfo.fkf();
					cout << "The fkf of '" << objName << "' is " << f.str() << ". Use it in the G function.\n";
				}
				cout << "\n";
			}
		}
	}
	
	// SecureInt
	cout << "\nSECUREINTs\n";
	for (int sid = 0; (sid = code.find("SecureInt",sid)) != -1; sid++)
	{
		if (!isComment(code,sid))
		{
			int semicolon = code.find(";", sid);
			for (int sii; ((sii = code.find("(", sid)) != -1) && (sii < semicolon);)
			{
				string objName = code.substr(sid, sii-sid);
				int sio = objName.find_last_of(" \t");
				if (sio > 0) objName = objName.substr(sio);
				if (!objName.compare("SecureInt")) objName = findObjectNameBefore(code, sid);
				///int sif = code.find(")", sii);
				int sif = findClosingBracket(code, sii+1);

				sii++;
				string params = code.substr(sii, sif-sii);
				string newParams = calcNewParamsSI(params);
				code = code.replace(sii, sif-sii, newParams);
				semicolon = code.find(";", sid);
				sid = sii + newParams.length();
				cout << "Object name: " << (objName.empty() ? "(no name)" : objName) << "\nParameters: " << newParams << "\n\n";
			}
		}
	}
	
	out.close();
	//ofstream out;
	out.open(filenameOut, ofstream::out);
	out << code;
	out.close();

	return 0;
}

/* Calculate the new parameters for a Cryptosystem */
string calcNewParamsCS(string params)
{
	Unumber p,q,k,rnd;
	string strPQ, strBeta, strTwoToBeta, strHalf, strEnc0, strEnc1, libgFilename, libgFunction, strGen = "";

	vector<string> v{explode(params,',')};
	switch (v.size())
	{
		case NUMBER_OF_CS_PARAMETERS:
			strPQ = v[0];
			strBeta = v[1];
			//strTwoToBeta = v[2];
			strHalf = v[2];
			//strEnc0 = v[4];
			//strEnc1 = v[5];
			libgFilename = v[3];
			libgFunction = v[4];
			strGen = v[5];
			break;
		case (NUMBER_OF_CS_PARAMETERS - 1):
			strPQ = v[0];
			strBeta = v[1];
			//strTwoToBeta = v[2];
			strHalf = v[2];
			//strEnc0 = v[4];
			//strEnc1 = v[5];
			libgFilename = v[3];
			libgFunction = v[4];
			//strGen = v[5];
			break;
		default:
			return params;
	}

	if (!isValidPQ(strPQ)) return params;

	try
	{
		unsigned beta = 0;
		trim(strBeta);
		if (strBeta.compare("__BETA"))
		{
			Unumber b(strBeta);
			beta = (unsigned) b.to_ull();
		}
		else if (paramBeta != 0)
		{
			beta = paramBeta;
		}

		sinfo = mountSensitiveInformation(strPQ, beta);

		Unumber n = sinfo.getN();
		beta = sinfo.getBeta();
		Unumber twoToBeta = sinfo.getTwoToBeta();
		Unumber zero = sinfo.encrypt(Unumber(0));
		Unumber one = sinfo.encrypt(Unumber(1));

		trim(strGen);
		if (!strGen.empty())
		{
			if (!strGen.compare("__GEN")) strGen = sinfo.access_g().str();
			strGen = ",\"" + strGen + "\"";
		}

		vector<string> localHalfTable = sinfo.getHalfTable();
		string strLocalHalfTable = "{" + vectorToString(localHalfTable) + "}";

		string newParams = "\"" + n.str() + "\"," + std::to_string(beta) + "," + strLocalHalfTable + "," + libgFilename + "," + libgFunction + strGen; // + "," + libgInit;

		return newParams;
	}
	catch (std::exception & e) { }

	return params;
}

/* Calculate the new parameters for a SecureInt */
string calcNewParamsSI(string params)
{
	vector<string> v{explode(params,',')};
	if (v.size() != NUMBER_OF_SI_PARAMETERS) return params;

	string strValue = v[0];
	string csName = v[1];

	if (!isSecureIntPrecompilerTag(strValue)) return params;

	try
	{
		int posI = strValue.find("(");
		int posF = strValue.find(")", posI);
		strValue = strValue.substr(posI+1, posF-posI-1);
		trim(strValue);
	
		Unumber value (strValue);

		int pos = indexOf(csList, csName);
		if (pos == -1) return params;

		sinfo = sinfoList[pos];
		value = sinfo.encrypt(value);

		string newParams = "\"" + value.str() + "\"," + csName;
		return newParams;
	}
	catch (std::exception & e) { }
	
	return params;
}

/* Find the bracket that closes a sequence of nested brackets */
int findClosingBracket(const string & code, int init)
{
	int countOpen = 1, countClose = 0;
	int posOpen, posClose;

	while (countOpen > countClose)
	{
		posOpen = code.find("(", init);
		posClose = code.find(")", init);

		if ((posOpen == -1) && (posClose == -1)) return -1;

		if ((posOpen == -1) || (posClose < posOpen))
		{
			if (!isComment(code, posClose)) countClose++;
			init = posClose + 1;
		}
		else
		{
			if (!isComment(code, posOpen)) countOpen++;
			init = posOpen + 1;
		}
	}

	return posClose;
}

/* Find the object name that is located before posF */
string findObjectNameBefore(const string & code, int posF)
{
	int posI = code.rfind(";", posF);
	if (posI == -1) posI = 0;
	int posE = code.find("=", posI);
	
	string str = "";
	if (posE > posI)
	{
		str = code.substr(posI+1,posE-posI-1);
		posI = str.find_last_of("\n");
		if (posI >= 0) str = str.substr(posI);
		trim(str);
	}
	
	return str;
}

/* Check if the string is a tag of a SecureInt value */
bool isSecureIntPrecompilerTag(const string & str)
{
	std::regex re("__E\\((0[xX])?[0-9a-fA-F]+\\)");
	std::cmatch m;
	return std::regex_match(str.c_str(), m, re);
}

/* Check if tag __PQ...__ in the code is valid  */
bool isValidPQ(const string & pqkrnd)
{
	try
	{
		string part = pqkrnd.substr(0,4);
		if (part.compare("__PQ")) return false;

		return true; //ish
	}
	catch (const std::exception & e) { } 

	return false;
}

/* Create a SensitiveInformation object based on a string in the format __PQ(p)(q)(k)(r)__ */
/* p, q, k, and r are optional */
SensitiveInformation mountSensitiveInformation(string & pqkrnd, unsigned beta)
{
	try
	{
		int posI = pqkrnd.find("(");
		int posF = pqkrnd.find(")", posI);
		string strP = pqkrnd.substr(posI+1, posF-posI-1);

		posI = pqkrnd.find("(", posF);
		posF = pqkrnd.find(")", posI);
		string strQ = pqkrnd.substr(posI+1, posF-posI-1);

		posI = pqkrnd.find("(", posF);
		posF = pqkrnd.find(")", posI);
		string strK = pqkrnd.substr(posI+1, posF-posI-1);

		posI = pqkrnd.find("(", posF);
		posF = pqkrnd.find(")", posI);
		string strRnd = pqkrnd.substr(posI+1, posF-posI-1);

		trim(strP);
		trim(strQ);
		trim(strK);
		trim(strRnd);
		
		//Unumber primeFrom (PRIME_FROM);
		//Unumber primeTo (PRIME_TO);
		Unumber primeFrom(1);
		primeFrom <<= primeMinExp;
		Unumber primeTo(1);
		primeTo <<= primeMaxExp;

		cout << "primeFrom: " << primeFrom.str() << "\tprimeTo: " << primeTo.str() << "\n";

		Unumber p   = (  strP.empty() ? prime(primeFrom, primeTo) : Unumber(strP));
		Unumber q   = (  strQ.empty() ? prime(primeFrom, primeTo) : Unumber(strQ));
		while (p == q) q = prime(primeFrom, primeTo);
		Unumber pq = p*q;
		Unumber k   = (  strK.empty() ? invertibleRandom(2, pq)   : Unumber(strK));
		Unumber rnd = (strRnd.empty() ? invertibleRandom(2, pq)   : Unumber(strRnd));

		cout << "P: " << p.str() << "\tQ: " << q.str() << "\tK: " << k.str() << "\tRND: " << rnd.str() << "\n";

		SensitiveInformation si(p,q,k,rnd,beta);
		si.calcHalfTable();
		return si;
	}
	catch (std::exception & e) { }

	return SensitiveInformation();
}


