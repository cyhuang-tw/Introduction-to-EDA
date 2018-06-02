#include "cirGate.h"

void INVGate::printCNF(vector<string>& cnf)
{
	int p1 = _id;
	int p2 = _fanin -> getID();
	string c1 = to_string((-1)*p1) + " " + to_string((-1)*p2) + " 0";
	string c2 = to_string(p1) + " " + to_string(p2) + " 0";
	cnf.push_back(c1);
	cnf.push_back(c2);
}

void ANDGate::printCNF(vector<string>& cnf)
{
	string c0 = "";
	for(unsigned i = 0; i < _fanin.size(); ++i){
		string c = to_string(_fanin[i] -> getID()) + " " + to_string((-1)*_id) + " 0";
		cnf.push_back(c);
		c0 += to_string((-1)*_fanin[i] -> getID()) + " ";
	}
	c0 += to_string(_id) + " 0";
	cnf.push_back(c0);
}

void ORGate::printCNF(vector<string>& cnf)
{
	string c0 = "";
	for(unsigned i = 0; i < _fanin.size(); ++i){
		string c = to_string((-1)*(_fanin[i] -> getID())) + " " + to_string(_id) + " 0";
		cnf.push_back(c);
		c0 += to_string(_fanin[i] -> getID()) + " ";
	}
	c0 += to_string((-1)*_id) + " 0";
	cnf.push_back(c0);
}

void NANDGate::printCNF(vector<string>& cnf)
{
	string c0 = "";
	for(unsigned i = 0; i < _fanin.size(); ++i){
		string c = to_string(_fanin[i] -> getID()) + " " + to_string(_id) + " 0";
		cnf.push_back(c);
		c0 += to_string((-1)*(_fanin[i] -> getID()));
	}
	c0 += to_string((-1)*_id) + " 0";
	cnf.push_back(c0);
}

void NORGate::printCNF(vector<string>& cnf)
{
	string c0 = "";
	for(unsigned i = 0; i < _fanin.size(); ++i){
		string c = to_string((-1)*(_fanin[i] -> getID())) + " " + to_string((-1)*_id) + " 0";
		cnf.push_back(c);
		c0 += to_string(_fanin[i] -> getID()) + " ";
	}
	c0 += to_string(_id) + " 0";
	cnf.push_back(c0);
}

void XORGate::printCNF(vector<string>& cnf)
{
	int p1 = _fanin[0] -> getID();
	int p2 = _fanin[1] -> getID();
	string c0 = to_string((-1)*p1) + " " + to_string((-1)*p2) + " " + to_string((-1)*_id) + " 0";
	string c1 = to_string((-1)*p1) + " " + to_string(p2) + " " + to_string(_id) + " 0";
	string c2 = to_string(p1) + " " + to_string((-1)*p2) + " " + to_string(_id) + " 0";
	string c3 = to_string(p1) + " " + to_string(p2) + " " + to_string((-1)*_id) + " 0";
	cnf.push_back(c0);
	cnf.push_back(c1);
	cnf.push_back(c2);
	cnf.push_back(c3);
}

void EQVGate::printCNF(vector<string>& cnf)
{
	int p1 = _fanin[0] -> getID();
	int p2 = _fanin[1] -> getID();
	string c0 = to_string(p1) + " " + to_string(p2) + " " + to_string(_id) + " 0";
	string c1 = to_string(p1) + " " + to_string((-1)*p2) + " " + to_string((-1)*_id) + " 0";
	string c2 = to_string((-1)*p1) + " " + to_string(p2) + " " + to_string((-1)*_id) + " 0";
	string c3 = to_string((-1)*p1) + " " + to_string((-1)*p2) + " " + to_string(_id) + " 0";
	cnf.push_back(c0);
	cnf.push_back(c1);
	cnf.push_back(c2);
	cnf.push_back(c3);
}

void BUFGate::printCNF(vector<string>& cnf)
{
	string c1 = to_string((-1)*(_fanin -> getID())) + " " + to_string(_id) + " 0";
	string c2 = to_string(_fanin -> getID()) + " " + to_string((-1)*_id) + " 0";
	cnf.push_back(c1);
	cnf.push_back(c2);
}