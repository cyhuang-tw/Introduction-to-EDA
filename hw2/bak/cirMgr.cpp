#include <fstream>
#include <algorithm>
#include "cirMgr.h"

void cirMgr::reset()
{
	for(map<string,cirGate*>::iterator iter = _gate1.begin(); iter != _gate1.end(); ++iter){
		delete iter -> second;
	}
	for(map<string,cirGate*>::iterator iter = _gate2.begin(); iter != _gate2.end(); ++iter){
		delete iter -> second;
	}
	for(map<string,cirGate*>::iterator iter = _PIList.begin(); iter != _PIList.end(); ++iter){
		delete iter -> second;
	}
	for(vector<cirGate*>::iterator iter = _POList.begin(); iter != _POList.end(); ++iter){
		delete *iter;
	}		
}

bool cirMgr::read(string& f1,string& f2)
{
	fstream file;
	file.open(f1,ios::in);
	if(!file.is_open())
		return false;

	string str;
	unsigned id = 1;

	while(getline(file,str)){
		if(str.find("#") != string::npos)
			continue;
		if(str.empty())
			continue;

		size_t beg = str.find_first_of("(");
		size_t end = str.find_first_of(")");
		size_t len = end - beg - 1;

		string pms = str.substr(beg + 1,len);

		vector<string> tokens;
		lexOptions(pms,tokens);

		size_t eq = str.find_first_of(" = ");
		string name = str.substr(beg + 1,len); //(identify name here)
		string type = str.substr(0,beg); //INPUT(name)
		
		if(eq != string::npos){	//name = TYPE(...)
			name = str.substr(0,eq);
			type = str.substr(eq + 3,beg - eq - 3);
		}

		cirGate* gate = 0;
		vector<cirGate*> fanin;

		if(type == "INPUT"){
			gate = new PIGate(name,id);
			++id;
			_PIList.insert(pair<string,cirGate*>(name,gate));
			continue;
		}
		if(type == "OUTPUT"){
			gate = new POGate(name,id);
			//_POList.insert(pair<string,cirGate*>(name,gate));
			_POList.push_back(gate);
			continue;
		}
		getFanin1(tokens,fanin);
		if(type == "AND"){
			gate = new ANDGate(name,id,fanin);
		}
		if(type == "OR"){
			gate = new ORGate(name,id,fanin);
		}
		if(type == "NAND"){
			gate = new NANDGate(name,id,fanin);
		}
		if(type == "NOR"){
			gate = new NORGate(name,id,fanin);
		}
		if(type == "INV" || type == "NOT"){
			gate = new INVGate(name,id,fanin);
		}
		if(type == "XOR"){
			gate = new XORGate(name,id,fanin);
		}
		if(type == "EQV"){
			gate = new EQVGate(name,id,fanin);
		}
		if(type == "BUF"){
			gate = new BUFGate(name,id,fanin);
		}

		if(gate){
			_gate1.insert(pair<string,cirGate*>(name,gate));
			++id;
		}
	}
	file.close();

	file.open(f2,ios::in);
	if(!file.is_open())
		return false;
/* second part */ /* second part */ /* second part */ /* second part */ /* second part */ /* second part */
	while(getline(file,str)){

		if(str.find("#") != string::npos)
			continue;
		if(str.empty())
			continue;
		
		size_t beg = str.find_first_of("(");
		size_t end = str.find_first_of(")");
		size_t len = end - beg - 1;

		string pms = str.substr(beg + 1,len);

		vector<string> tokens;
		lexOptions(pms,tokens);

		size_t eq = str.find_first_of(" = ");
		string name = str.substr(beg + 1,len); //(identify name here)
		string type = str.substr(0,beg); //INPUT(name)
		
		if(eq != string::npos){	//name = TYPE(...)
			name = str.substr(0,eq);
			type = str.substr(eq + 3,beg - eq - 3);
		}

		cirGate* gate = 0;
		vector<cirGate*> fanin;
		if(type == "INPUT" || type == "OUTPUT")
			continue;
		getFanin2(tokens,fanin);

		if(type == "AND"){
			gate = new ANDGate(name,id,fanin);
		}
		if(type == "OR"){
			gate = new ORGate(name,id,fanin);
		}
		if(type == "NAND"){
			gate = new NANDGate(name,id,fanin);
		}
		if(type == "NOR"){
			gate = new NORGate(name,id,fanin);
		}
		if(type == "INV" || type == "NOT"){
			gate = new INVGate(name,id,fanin);
		}
		if(type == "XOR"){
			gate = new XORGate(name,id,fanin);
		}
		if(type == "EQV"){
			gate = new EQVGate(name,id,fanin);
		}
		if(type == "BUF"){
			gate = new BUFGate(name,id,fanin);
		}

		if(gate){
			_gate2.insert(pair<string,cirGate*>(name,gate));
			++id;
		}
	}

	_varNum = id;

	return true;

}


size_t cirMgr::strGetTok(string& str, string& tok, size_t pos = 0)
{
	size_t begin = str.find_first_not_of(",",pos);
	if(begin == string::npos) { tok = ""; return begin; }
	size_t end = str.find_first_of(",",begin);

	tok = str.substr(begin,end - begin);

	return end;
}

void cirMgr::lexOptions(string& str,vector<string>& tokens)
{
	string tok;
	str.erase(remove(str.begin(),str.end(),' '),str.end());
	size_t n = strGetTok(str,tok);
	while(tok.size()){
		tokens.push_back(tok);
		n = strGetTok(str,tok,n);
	}
}

void cirMgr::getFanin1(vector<string>& nameList,vector<cirGate*>& gateList)
{
	for(unsigned i = 0; i < nameList.size(); ++i){
		map<string,cirGate*>::iterator iter = _gate1.find(nameList[i]);
		if(iter != _gate1.end()){
			gateList.push_back(iter -> second);
			continue;
		}
		iter = _PIList.find(nameList[i]);
		if(iter != _PIList.end()){
			gateList.push_back(iter -> second);
		}
	}
}

void cirMgr::getFanin2(vector<string>& nameList,vector<cirGate*>& gateList)
{
	for(unsigned i = 0; i < nameList.size(); ++i){
		map<string,cirGate*>::iterator iter = _gate2.find(nameList[i]);
		if(iter != _gate2.end()){
			gateList.push_back(iter -> second);
			continue;
		}
		iter = _PIList.find(nameList[i]);
		if(iter != _PIList.end()){
			gateList.push_back(iter -> second);
		}
	}
}

void cirMgr::print()
{
	for(map<string,cirGate*>::iterator iter = _gate1.begin(); iter != _gate1.end(); ++iter){
		cout << (iter -> second) -> getName();
		cout << " ";
		cout << (iter -> second) -> getType();
		cout << endl;
		cout << "fanin(s):";
		(iter -> second) -> pFanin();
	}
	for(map<string,cirGate*>::iterator iter = _gate2.begin(); iter != _gate2.end(); ++iter){
		cout << (iter -> second) -> getName();
		cout << " ";
		cout << (iter -> second) -> getType();
		cout << endl;
		cout << "fanin(s):";
		(iter -> second) -> pFanin();
	}
	for(map<string,cirGate*>::iterator iter = _PIList.begin(); iter != _PIList.end(); ++iter){
		cout << (iter -> second) -> getName();
		cout << " ";
		cout << (iter -> second) -> getType();
		cout << endl;
	}
	for(vector<cirGate*>::iterator iter = _POList.begin(); iter != _POList.end(); ++iter){
		cout << (*iter) -> getName();
		cout << " ";
		cout << (*iter) -> getType();
		cout << endl;
	}
}

void cirMgr::printSAT(string& str)
{
	fstream file;
	file.open(str,ios::out);
	string s = "";

	vector<cirGate*> xorGate;

	for(unsigned i = 0; i < _POList.size(); ++i){ //XOR each output in ckt1 and ckt2
		cirGate* g = 0;
		map<string,cirGate*>::iterator iter;
		vector<cirGate*> fanin;
		iter = _gate1.find(_POList[i] -> getName());
		fanin.push_back(iter -> second);
		iter = _gate2.find(_POList[i] -> getName());
		fanin.push_back(iter -> second);
		g = new XORGate(s,_varNum,fanin);
		xorGate.push_back(g);
		++_varNum;
	}

	cirGate* g = 0;

	if(_POList.size() > 1){
		g = new ORGate(s,_varNum,xorGate);
		++_varNum;
	} //if multiple outputs

	vector<string> cnf;

	for(map<string,cirGate*>::iterator iter = _gate1.begin(); iter != _gate1.end(); ++iter){
		(iter -> second) -> printCNF(cnf);
	}

	for(map<string,cirGate*>::iterator iter = _gate2.begin(); iter != _gate2.end(); ++iter){
		(iter -> second) -> printCNF(cnf);
	}

	for(unsigned i = 0; i < xorGate.size(); ++i){
		xorGate[i] -> printCNF(cnf);
		delete xorGate[i];
	}

	if(g){
		g -> printCNF(cnf);
		cnf.push_back(to_string(g -> getID()) + " 0");
		delete g;
	}

	file << "p cnf ";
	file << _varNum - 1 << " " << cnf.size() << endl;
	for(unsigned i = 0; i < cnf.size(); ++i){
		file << cnf[i] << endl;
	}

	file.close();
}