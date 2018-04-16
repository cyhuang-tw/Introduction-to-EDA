#include <iostream>
#include <fstream>
#include "vMap.h"

using namespace std;

int main(int argc, char *argv[]){
	vMap map;

	fstream* inFile = new fstream;
	inFile -> open(argv[1],ios::in);

	map.read(inFile);
	inFile -> close();

	fstream* outFile = new fstream;
	outFile -> open(argv[2],ios::out);
	map.print(outFile);
	outFile -> close();

	delete inFile;
	delete outFile;

	return 0;
}