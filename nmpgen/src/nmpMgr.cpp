#include "nmpMgr.h"
#include <fstream>
#include <algorithm>
#include <cmath>

void nmpMgr::init()
{
	_base = 93;
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

	_name.insert(std::make_pair(preName,postName));
}
/*
void nmpMgr::print()
{
	for(unsigned i = 0; i < _name.size(); ++i){
		cout << _name[i].first << " " << _name[i].second << endl;
	}
}
*/
void nmpMgr::optimize()
{
	for(map<string,string>::iterator iter = _name.begin(); iter != _name.end(); ++iter){
		_preName.push_back(iter -> first);
		_postName.push_back(iter -> second);
	}

	std::sort(_preName.begin(),_preName.end());
	std::sort(_postName.begin(),_postName.end());

	for(unsigned i = 0; i < _name.size(); ++i){
		_preMap.insert(make_pair(_preName[i],i));
		_postMap.insert(make_pair(_postName[i],i));
	}

	map<string,string>::iterator iter;

	for(unsigned i = 0; i < _preName.size(); ++i){
		iter = _name.find(_preName[i]);
		unsigned num = (_postMap.find(iter -> second)) -> second;
		_postInt.push_back(num);
	}	
}

void nmpMgr::printFile(string str)
{
	fstream outFile;
	outFile.open(str,ios::out);

	for(unsigned i = 0; i < _postInt.size(); ++i){
		string str = int2str(_postInt[i]);
		if(_postInt[i] == i)
			str = "";
		outFile << str << endl;

		_postStr.push_back(str);
	}

	outFile.close();
}

string nmpMgr::int2str(unsigned num)
{
	//A -> 65	B-> 66	...	Z -> 90
	unsigned radix = ceil(log(_name.size())/log(float(_base)));
	unsigned mod = 0;
	string str = "";
	for(unsigned i = 0; i < radix; ++i){
		mod = num % _base;
		num = (num-mod)/_base;
		str += char(33 + mod);
	}
	return str;
}

unsigned nmpMgr::str2int(string& str)
{
	unsigned radix = ceil(log(_name.size())/log(float(_base)));
	unsigned num = 0;
	for(unsigned i = 0; i < str.length(); ++i){
		num += (int(str[i])-33)*pow(_base,i);
	}
	return num;
}

bool nmpMgr::verify()
{
	map<string,string>::iterator iter;

	for(iter = _name.begin(); iter != _name.end(); ++iter){
		unsigned idx = (_preMap.find(iter -> first)) -> second; 
		string code = _postStr[idx];
		unsigned pos = str2int(code);
		if(code == "")
			pos = idx;
		if(_postName[pos] != iter -> second)
			return false;
	}
	return true;
}