#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "cirGate.h"

using namespace std;

#ifndef cirMgr_H
#define cirMgr_H

class cirMgr;

class cirMgr
{
public:
	cirMgr() { init(); }
	~cirMgr() { reset(); }
	bool read(string&,string&);
	void printSAT(string&);
	void print();

private:
	void init() { _varNum = 0; };
	void reset();
	size_t strGetTok(string&,string&,size_t);
	void lexOptions(string&,vector<string>&);
	void getFanin1(vector<string>&,vector<cirGate*>&);
	void getFanin2(vector<string>&,vector<cirGate*>&);

	map<string,cirGate*> _gate1;
	map<string,cirGate*> _gate2;
	map<string,cirGate*> _PIList;
	//map<string,cirGate*> _POList;
	vector<cirGate*> _POList;

	unsigned _varNum;

};

#endif