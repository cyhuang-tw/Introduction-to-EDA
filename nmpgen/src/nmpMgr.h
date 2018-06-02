#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class nmpMgr;

class nmpMgr
{
public:
	nmpMgr() { init(); }
	~nmpMgr() { reset(); }
	bool read(string);
	void print();

private:
	void init();
	void reset();
	void lexInfo(string&);
	vector<pair<string,string> > _name;
};