#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

using namespace std;

class nmpMgr;

class nmpMgr
{
public:
	nmpMgr() { init(); }
	~nmpMgr() { reset(); }
	bool read(string);
	void optimize();
	void printFile(string);
	bool verify();
	//void print();

private:
	void init();
	void reset();
	void lexInfo(string&);
	string int2str(unsigned);
	unsigned str2int(string&);

	//data member
	map<string,string> _name;
	vector<string> _preName;
	vector<string> _postName;
	map<string,unsigned> _preMap;
	map<string,unsigned> _postMap;
	vector<unsigned> _postInt;
	vector<string> _postStr;
	vector<char> _baseTable;
	unsigned _base;
};