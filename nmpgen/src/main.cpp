#include <iostream>
#include "nmpMgr.h"

nmpMgr mgr;

using namespace std;

int main(int argc, char *argv[]){

	if(argc != 2)
		return 0;

	string file = argv[1];
	string outFile = argv[2];

	if(!mgr.read(file))
		return 0;

	mgr.optimize();
	mgr.printFile(outFile);

	return 0;
}