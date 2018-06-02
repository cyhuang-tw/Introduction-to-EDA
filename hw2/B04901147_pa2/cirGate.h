#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#ifndef cirGate_H
#define cirGate_H

class cirGate;
class PIGate;
class POGate;
class INVGate;
class ANDGate;
class ORGate;
class NANDGate;
class NORGate;
class XORGate;
class EQVGate;
class BUFGate;

class cirGate
{
public:
	cirGate(): _name("0"), _id(0) {}
	//cirGate(string name): _name(name) {}
	virtual void printCNF(vector<string>&) = 0; //pass the vector and store CNF in it, avoiding copying.
	virtual string getType() = 0;
	virtual void pFanin() {}
	string getName() { return _name; }
	int getID() { return _id; }

protected:
	string _name;
	int _id;
};

class PIGate: public cirGate
{
public:
	PIGate(string& n, unsigned id) { _name = n; _id = id; }
	string getType() { return "PI"; }
	void printCNF(vector<string>&) override {}

private:

};

class POGate: public cirGate
{
public:
	POGate(string& n, unsigned id) { _name = n; _id = id; }
	string getType() { return "PO"; }
	void printCNF(vector<string>&) override {}

private:
	cirGate* _fanin;
};

class INVGate: public cirGate
{
public:
	INVGate(string& n, unsigned id,vector<cirGate*>& f) { _name = n; _id = id; _fanin = *(f.begin()); }
	string getType() { return "INV"; }
	void pFanin() { cout << (_fanin -> getName()) << endl; }
	void printCNF(vector<string>&) override;

private:
	cirGate* _fanin;

};

class ANDGate: public cirGate
{
public:
	ANDGate(string& n, unsigned id,vector<cirGate*>& f) { _name = n; _id = id; _fanin = f; }
	string getType() { return "AND"; }
	void pFanin() { for(unsigned i = 0; i < _fanin.size(); ++i) cout << (_fanin[i] -> getName()) << " "; cout << endl; }
	void printCNF(vector<string>&) override;


private:
	vector<cirGate*> _fanin;
};

class ORGate: public cirGate
{
public:
	ORGate(string& n, unsigned id,vector<cirGate*>& f) { _name = n; _id = id; _fanin = f; }
	string getType() { return "OR"; }
	void pFanin() { for(unsigned i = 0; i < _fanin.size(); ++i) cout << (_fanin[i] -> getName()) << " "; cout << endl; }
	void printCNF(vector<string>&) override;

private:
	vector<cirGate*> _fanin;
};

class NANDGate: public cirGate
{
public:
	NANDGate(string& n, unsigned id,vector<cirGate*>& f) { _name = n; _id = id; _fanin = f; }
	string getType() { return "NAND"; }
	void pFanin() { for(unsigned i = 0; i < _fanin.size(); ++i) cout << (_fanin[i] -> getName()) << " "; cout << endl; }
	void printCNF(vector<string>&);

private:
	vector<cirGate*> _fanin;

};

class NORGate: public cirGate
{
public:
	NORGate(string& n, unsigned id,vector<cirGate*>& f) { _name = n; _id = id; _fanin = f; }
	string getType() { return "NOR"; }
	void pFanin() { for(unsigned i = 0; i < _fanin.size(); ++i) cout << (_fanin[i] -> getName()) << " "; cout << endl; }
	void printCNF(vector<string>&);

private:
	vector<cirGate*> _fanin;

};

class XORGate: public cirGate
{
public:
	XORGate(string& n, unsigned id,vector<cirGate*>& f) { _name = n; _id = id; _fanin = f; }
	string getType() { return "XOR"; }
	void pFanin() { for(unsigned i = 0; i < _fanin.size(); ++i) cout << (_fanin[i] -> getName()) << " "; cout << endl; }
	void printCNF(vector<string>&);

private:
	vector<cirGate*> _fanin;

};

class EQVGate: public cirGate
{
public:
	EQVGate(string& n, unsigned id,vector<cirGate*>& f) { _name = n; _id = id; _fanin = f; }
	string getType() { return "EQV"; }
	void pFanin() { for(unsigned i = 0; i < _fanin.size(); ++i) cout << (_fanin[i] -> getName()) << " "; cout << endl; }
	void printCNF(vector<string>&);

private:
	vector<cirGate*> _fanin;

};

class BUFGate: public cirGate
{
public:
	BUFGate(string& n, unsigned id,vector<cirGate*>& f) { _name = n; _id = id; _fanin = *(f.begin()); }
	string getType() { return "BUF"; }
	void pFanin() { cout << (_fanin -> getName()) << endl; }
	void printCNF(vector<string>&);

private:
	cirGate* _fanin;
};

#endif