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

void nmpMgr::strOpt(vector<string>& list)
{
	unsigned count = 0;
	for(unsigned i = 0; i < _postInt.size(); ++i){
		string str = int2str(_postInt[i]);
		if(_postInt[i] == i){
			++count;
			if(i == _postInt.size() - 1){
				if(count == 1)
					list.push_back("");
				else
					list.push_back("*" + int2str(count));
			}
			continue;
		}
		if(count != 0 && count != 1)
			list.push_back("*" + int2str(count));
		if(count == 1)
			list.push_back("");
		count = 0;
		list.push_back(str);
	}

	string hold = "";
	size_t ptr = 0;

	for(unsigned i = 0; i < list.size(); ++i){
		if(list[i].find("*") != string::npos || list[i].empty()){
			hold = "";
			continue;
		}
		if(hold.empty()){
			hold = list[i];
			continue;
		}
		string str = "";
		for(unsigned j = list[i].size() - 1; j >= 0; --j){
			if(list[i][j] != hold[j]){
				str = list[i].substr(0,j+1);
				if(str == list[i])
					hold = list[i];
				list[i] = str;
				break;
			}
		}
	}	
}

void nmpMgr::printFile(string str)
{
	//print a python script
	fstream outFile;
	outFile.open(str.c_str(),ios::out);

	outFile << "import sys" << endl;
	outFile << "import json" << endl;

	bool same = true;
	for(unsigned i = 0; i < _postInt.size(); ++i){
		if(_postInt[i] != i){
			same = false;
			break;
		}
	}

	if(same){
		outFile << "_in = json.load(open(sys.argv[1],'r'))" << endl;
		outFile << "_write = open(sys.argv[2],'w')" << endl;
		outFile << "left = _in[0]" << endl;
		outFile << "right = _in[1]" << endl;
		outFile << "left.sort()" << endl;
		outFile << "right.sort()" << endl;
		outFile << "out_dict = dict()" << endl;
		outFile << "for i in range(len(left)):" << endl;
		outFile << "	" << "ans = right[i]" << endl;
		outFile << "	" << "out_dict[left[i]] = ans" << endl;
		outFile << "write_dict = json.dumps(out_dict)" << endl;
		outFile << "_write.write(write_dict)" << endl;
		return;
	}

	outFile << "def ascii_62(char):" << endl;
	outFile << "	" << "asc = ord(char)" << endl;
	outFile << "	" << "if(asc > 96):" << endl;
	outFile << "		" << "return (35 + (asc - 96))" << endl;
	outFile << "	" << "elif (asc > 64):" << endl;
	outFile << "		" << "return (9 + (asc - 64))" << endl;
	outFile << "	" << "else:" << endl;
	outFile << "		" << "return (asc - 48)" << endl;

	outFile << "def str2int(s):" << endl;
	outFile << "	" << "index = 0" << endl;
	outFile << "	" << "for i in range(len(s)):" << endl;
	outFile << "		" << "index += ascii_62(s[i]) * (62 ** i)" << endl;
	outFile << "	" << "return index" << endl;

	vector<string> list;
	strOpt(list);

	outFile << "digit" << " = " << ceil(log(_name.size())/log(float(_base))) << endl;

	outFile << "r = " << "[";
	for(unsigned i = 0; i < list.size();){
		outFile << "\"" << list[i] << "\"";
		if(++i != list.size())
			outFile << ",";
	}
	outFile << "]" << endl;

	outFile << "table = []" << endl;
	outFile << "hold = \"\"" << endl;
	outFile << "for x in range(len(r)):" << endl;
	outFile << "	" << "rpt = r[x].find(\"*\")" << endl;
	outFile << "	" << "if (rpt != -1):" << endl;
	outFile << "		" << "for y in range(str2int(r[x][rpt+1:])):" << endl;
	outFile << "			" << "table.append(\"\")" << endl;
	outFile << "		" << "hold = \"\"" << endl;
	outFile << "		" << "continue" << endl;
	outFile << "	" << "if (r[x] == \"\"):" << endl;
	outFile << "		" << "table.append(\"\")" << endl;
	outFile << "		" << "hold = \"\"" << endl;
	outFile << "		" << "continue" << endl;
	outFile << "	" << "if (hold == \"\" or len(r[x]) == digit):" << endl;
	outFile << "		" << "hold = s = r[x]" << endl;
	outFile << "	" << "if(len(r[x]) != digit):" << endl;
	outFile << "		" << "s = r[x] + hold[len(r[x]):]" << endl;
	outFile << "	" << "table.append(s)" << endl;

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
	outFile << "		" << "index = str2int(table[i])" << endl;
	outFile << "		" << "ans = right[index]" << endl;
	outFile << "	" << "out_dict[left[i]] = ans" << endl;
	outFile << "write_dict = json.dumps(out_dict)" << endl;
	outFile << "_write.write(write_dict)" << endl;

	outFile.close();
}

string nmpMgr::int2str(unsigned num)
{
	unsigned digit = ceil(log(_name.size())/log(float(_base)));
	unsigned mod = 0;
	string str = "";
	for(unsigned i = 0; i < digit; ++i){
		mod = num % _base;
		num = (num-mod)/_base;
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
	}
	return num;
}

bool nmpMgr::verify(vector<string>& list)
{
	if(list.empty())
		return true;
	unsigned digit = ceil(log(_name.size())/log(float(_base)));
	unsigned code = 0;
	string hold = list[0];
	string str = "";
	vector<string> rList;
	for(unsigned i = 0; i < list.size(); ++i){
		str = list[i];
		if(list[i].find("*") != string::npos){
			str = list[i].substr(1);
			code = str2int(str);
			for(unsigned j = 0; j < code; ++j)
				rList.push_back("");
			hold = "";
			continue;
		}
		if(list[i] == ""){
			rList.push_back("");
			hold = "";
			continue;
		}

		if(hold.empty())
			hold = list[i];
		if(list[i].size() == digit)
			hold = list[i];
		if(list[i].size() != digit){
			str = list[i] + hold.substr(list[i].size());
		}
		rList.push_back(str);
	}
	if(rList.size() != _name.size()){
		cout << rList.size() << " " << _name.size() << endl;
		cout << "incorrect size" << endl;
		return false;
	}

	for(unsigned i = 0; i < rList.size(); ++i){
		unsigned idx = str2int(rList[i]);
		if(rList[i] == "")
			idx = i;
		string ans = (_name.find(_preName[i])) -> second;
		if(_postName[idx] != ans){
			cout << "Error: " << _postName[idx] << " != " << ans << endl;
			return false;
		}

	}
	cout << "Verification passed!" << endl;
	return true;
}