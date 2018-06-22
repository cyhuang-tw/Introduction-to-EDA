#include <iostream>
#include "nmpMgr.h"

nmpMgr mgr;

using namespace std;

int main(int argc, char *argv[]){
/*
	if(argc < 2){
		cerr << "The number of parameters is incorrect." << endl;
		return 0;
	}
*/
	string file = argv[1];
	string outFile = file + ".py";

	if(!mgr.read(file)){
		cerr << "Cannot open file: " << argv[1] << endl;
		return 0;
	}

	mgr.optimize();
	mgr.printFile(outFile);
	//mgr.print();
	if(mgr.verify())
		cout << "Verification passed..." << endl;
	else
		cout << "Verification NOT passed..." << endl;

	return 0;
}