#include "nmpMgr.h"
#include <fstream>
#include <algorithm>
#include <cmath>

void nmpMgr::init()
{
	for(unsigned i = 0; i < 10; ++i){	//0-9
		_baseTable.push_back(char(48 + i));
	}
	for(unsigned i = 0; i < 26; ++i){	//A-Z
		_baseTable.push_back(char(65 + i));
	}
	for(unsigned i = 0; i < 26; ++i){	//a-z
		_baseTable.push_back(char(97 + i));
	}

	_base = _baseTable.size();
	
	return;
}

void nmpMgr::reset()
{
	return;
}


bool nmpMgr::read(string fileName)
{
	fstream file(fileName.c_str(),ios::in);
	//file.open(fileName,ios::in);

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
	//print a python script
	fstream outFile;
	outFile.open(str.c_str(),ios::out);

	outFile << "import sys" << endl;
	outFile << "import json" << endl;
	outFile << "def ascii_62(char):" << endl;
	outFile << "	" << "asc = ord(char)" << endl;
	outFile << "	" << "if(asc > 96):" << endl;
	outFile << "		" << "return (35 + (asc - 96))" << endl;
	outFile << "	" << "elif (asc > 64):" << endl;
	outFile << "		" << "return (9 + (asc - 64))" << endl;
	outFile << "	" << "else:" << endl;
	outFile << "		" << "return (asc - 48)" << endl;

	outFile << "table = " << "[";
	for(unsigned i = 0; i < _postInt.size();){
		string str = int2str(_postInt[i]);
		if(_postInt[i] == i)
			str = "";
		outFile << "\"" << str << "\"";

		_postStr.push_back(str);
		if(++i != _postInt.size())
			outFile << ",";
	}
	outFile << "]" << endl;
	outFile << "_in = json.load(open(sys.argv[1],'r'))" << endl;
	outFile << "_write = open(sys.argv[2],'w')" << endl;
	outFile << "left = _in[0]" << endl;
	outFile << "right = _in[1]" << endl;
	outFile << "left.sort()" << endl;
	outFile << "right.sort()" << endl;
	outFile << "out_dict = dict()" << endl;
	outFile << "for i in range(len(table)):" << endl;
	outFile << "	" << "if (table[i] == \"\"):" << endl;
	outFile << "		" << "ans = right[i]" << endl;
	outFile << "	" << "else:" << endl;
	outFile << "		" << "index = 0" << endl;
	outFile << "		" << "for j in range(len(table[i])):" << endl;
	outFile << "			" << "index += ascii_62(table[i][j])*(62**j)" << endl;
	outFile << "		" << "ans = right[index]" << endl;
	outFile << "	" << "out_dict[left[i]] = ans" << endl;
	outFile << "write_dict = json.dumps(out_dict)" << endl;
	outFile << "_write.write(write_dict)" << endl;

	outFile.close();
}

string nmpMgr::int2str(unsigned num)
{
	//A -> 65	B-> 66	...	Z -> 90
	unsigned digit = ceil(log(_name.size())/log(float(_base)));
	unsigned mod = 0;
	string str = "";
	for(unsigned i = 0; i < digit; ++i){
		mod = num % _base;
		num = (num-mod)/_base;
		//str += char(33 + mod);
		str += _baseTable[mod];
	}
	return str;
}

unsigned nmpMgr::str2int(string& str)
{
	unsigned radix = ceil(log(_name.size())/log(float(_base)));
	unsigned num = 0;
	for(unsigned i = 0; i < str.length(); ++i){
		int tmp = (int)(str[i]);
		if(tmp < 58){	//0-9
			num += (tmp - 48)*pow(_base,i);
			continue;
		}
		if(tmp < 91){	//A-Z
			num += (10 + (tmp - 65))*pow(_base,i);
			continue;
		}
		num += (36 + (tmp - 97))*pow(_base,i);
		//num += (int(str[i])-33)*pow(_base,i);
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