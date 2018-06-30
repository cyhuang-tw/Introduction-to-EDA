#include <iostream>
#include <ctime>
#include "nmpMgr.h"

nmpMgr mgr;

using namespace std;

int main(int argc, char *argv[]){

	if(argc != 3)
		return 0;

	//clock_t start, end;

	string file = argv[1];
	string outFile = argv[2];

	//start = clock();

	if(!mgr.read(file))
		return 0;

	mgr.optimize();
	mgr.printFile(outFile);

	//end = clock();

	//cout << "Elapsed time: " << ((double)(end - start))/CLOCKS_PER_SEC << endl;

	return 0;
}