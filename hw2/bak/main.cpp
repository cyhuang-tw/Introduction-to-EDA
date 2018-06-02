#include "cirMgr.h"
#include <string>

cirMgr mgr;

using namespace std;

int main(int argc,char *argv[])
{
	string f1 = argv[1];
	string f2 = argv[2];
	string f3 = argv[3];

	mgr.read(f1,f2);
	mgr.printSAT(f3);

	return 0;
}