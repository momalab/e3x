/*******************************************
* New York University in Abu Dhabi (NYUAD) *
* MoMAlab                                  *
* Author: Eduardo Chielle                  *
* eduardo.chielle@nyu.edu        2016-2017 *
********************************************/

#include <fstream>
#include <iostream>
#include "sensitive_information.h"
#include "util.h"

using namespace std;

void decrypt(string, string, SensitiveInformation);
SensitiveInformation loadCryptosystemParams(string);

int main(int argc, char *argv[])
{
	if (argc <= 3)
	{
		cout << "Invalid arguments.\n";
		return 1;
	}

	string dataInFilename = argv[1];
	string dataOutFilename = argv[2];
	string cryptosystemFilename = argv[3];

	// Loading Cryptosystem parameters and Instantiating SensitiveInformation
	SensitiveInformation sinfo = loadCryptosystemParams(cryptosystemFilename);

	decrypt(dataInFilename, dataOutFilename, sinfo);

	return 0;
}

/* Read filenameIn, decrypts its content by line and write to the filenameOut */
void decrypt(string filenameIn, string filenameOut, SensitiveInformation sinfo)
{
	ifstream in;
	ofstream out;
	in.open(filenameIn, ifstream::in);
	out.open(filenameOut, ofstream::out);
	
	Unumber R, result;
	string line;

	getline(in, line);
	while (in)
	{
		trim(line);
		if (!line.empty())
		{
			vector<string> items = explode(line, ' ');
			for (unsigned i = 0; i < items.size(); )
			{
				//cout << items[i];
				if (isNumber(items[i]))
				{
					//cout << " is number\n";
					Unumber encValue (items[i]);
					result = sinfo.decrypt(encValue, &R);
					out << result.str();
				}
				else
				{
					//cout << " NET\n";
					out << items[i];
				}
				
				if (++i < items.size()) out << " ";
			}
		}
		out << "\n";
		getline(in, line);
	}

	in.close();
	out.close();
}

/* Read and parse the cryptosystem file, usually CS.txt. */
/* And creates a SensitiveInformation file used for decryption */
SensitiveInformation loadCryptosystemParams(string filename)
{
	ifstream in;
	in.open(filename, ifstream::in);
	stringstream buffer;
	buffer << in.rdbuf();
	string text = buffer.str();
	in.close();

	int len = 9;
	int semicolon[len];
	semicolon[0] = text.find(";") + 1;
	for (int i = 1; i < len; i++)
	{
		semicolon[i] = text.find(";", semicolon[i-1]) + 1;
	}
	//int newLine = text.find("\n") + 1;

	string strP	= text.substr(semicolon[0], semicolon[1]-semicolon[0]-1);
	string strQ	= text.substr(semicolon[1], semicolon[2]-semicolon[1]-1);
	string strK 	= text.substr(semicolon[2], semicolon[3]-semicolon[2]-1);
	string strBeta	= text.substr(semicolon[3], semicolon[4]-semicolon[3]-1);

	Unumber p,q,k,beta;
	p = Unumber(strP);
	q = Unumber(strQ);
	k = Unumber(strK);
	beta = Unumber(strBeta);

	SensitiveInformation si(p,q,k);
	si.setBeta(beta.to_ull());

	return si;
}

