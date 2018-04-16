#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#ifndef vMap_H
#define vMap_H

class vMap;
class Node;


class vMap
{
	typedef std::pair<int,int> via;
public:
	vMap(): _map(0), _viaList(0), _xDim(0), _yDim(0), _vNum(0) {};
	~vMap() { clear(); }
	bool read(std::fstream*);
	void print(std::fstream*);

private:
	void clear();
	void lex(std::string&,int&,int&);
	void printXY(std::string&,int,int,int);
	std::string xy2str(int,int,int);
	std::string gen1str(std::vector<std::string>&,std::string);
	Node& pos(int,int);

	Node** _map;
	via* _viaList;
	std::vector<via> _rviList;

	unsigned _xDim;
	unsigned _yDim;
	unsigned _vNum;

};

class Node
{
	friend class vMap;
	//member functions
	Node(): _rvi(false), _via(false) {};
	bool isRvi() { return _rvi; }
	bool isVia() { return _via; }
	bool isUsed() { return (_rvi || _via); }
	void setVia() { _via = true; }
	void setRvi() { _rvi = true; }


	//data member
	bool _rvi;
	bool _via;


};

#endif