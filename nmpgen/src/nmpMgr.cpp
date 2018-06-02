#include "nmpMgr.h"
#include <fstream>
#include <algorithm>

void nmpMgr::init()
{
	return;
}

void nmpMgr::reset()
{
	return;
}


bool nmpMgr::read(string fileName)
{
	fstream file;
	file.open(fileName,ios::in);

	if(!file.is_open()) //in case that file name is not correct, avoiding crash
		return false;

	string info = "";

	while(getline(file,info)){
		if(info == "{" || info == "}" || info.empty()) //skip starting "{" and ending "}" in the file
			continue;

		lexInfo(info); //parse the string and store into vector
	}

	return true;
}

void nmpMgr::lexInfo(string& str)
{
	str.erase(remove(str.begin(),str.end(),' '),str.end()); //remove white space in string
	str.erase(remove(str.begin(),str.end(),'"'),str.end()); //remove " in string
	str.erase(remove(str.begin(),str.end(),','),str.end()); //remove "," in string, usually at the end of string, except for the last string in file

	size_t found = str.find(":"); //"name_1":"name_2"

	if(found == string::npos) return;

	string preName = str.substr(0,found);
	string postName = str.substr(found+1);

	_name.push_back(std::make_pair(preName,postName));
}

void nmpMgr::print()
{
	for(unsigned i = 0; i < _name.size(); ++i){
		cout << _name[i].first << " " << _name[i].second << endl;
	}
}