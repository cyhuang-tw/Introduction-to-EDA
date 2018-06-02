#include <iostream>
#include "nmpMgr.h"

nmpMgr mgr;

using namespace std;

int main(int argc, char *argv[]){

	if(argc != 3){
		cerr << "The number of parameters is incorrect." << endl;
		return 0;
	}

	string file = argv[1];

	mgr.read(file);

	mgr.print();

	return 0;
}