#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "vMap.h"

bool vMap::read(std::fstream* file)
{
	if(!(file -> is_open())){
		std::cerr << "Error: Cannot open the file!" << std::endl;
		return false;
	}

	std::string str;
	std::getline(*file,str);
	_vNum = std::stoi(str);
	str.clear();
	//std::cout << "The number of vias is " << _vNum << "." << std::endl;
	_viaList = new via[_vNum];

	for(unsigned i = 0; i < _vNum; ++i){
		std::getline(*file,str);
		int x = 0, y = 0;
		lex(str,x,y);
		_viaList[i] = std::make_pair(x,y);
		if(x > _xDim) _xDim = x;
		if(y > _yDim) _yDim = y;
	}

	_map = new Node*[_xDim + 5];
	for(unsigned i = 0; i < _xDim + 5; ++i){
		_map[i] = new Node[_yDim + 5];
	}

	for(unsigned i = 0; i < _vNum; ++i){
		int& x = _viaList[i].first;
		int& y = _viaList[i].second;
		pos(x,y).setVia();
	}

	for(unsigned i = 0; i < _vNum; ++i){
		int x = _viaList[i].first;
		int y = _viaList[i].second;
		if(!pos(x-1,y).isUsed()) { pos(x-1,y).setRvi(); _rviList.push_back(std::make_pair(x-1,y)); }
		if(!pos(x+1,y).isUsed()) { pos(x+1,y).setRvi(); _rviList.push_back(std::make_pair(x+1,y)); }
		if(!pos(x,y-1).isUsed()) { pos(x,y-1).setRvi(); _rviList.push_back(std::make_pair(x,y-1)); }
		if(!pos(x,y+1).isUsed()) { pos(x,y+1).setRvi(); _rviList.push_back(std::make_pair(x,y+1)); }
	}

	//std::cout << "Initialization finished." << std::endl;

	return true;

}

void vMap::print(std::fstream* file)
{
	*file << "Maximize" << std::endl;

	std::vector<std::vector<std::string>*> maxList;
	for(unsigned i = 0; i < _vNum; ++i){
		int x = _viaList[i].first;
		int y = _viaList[i].second;
		std::vector<std::string>* list = new std::vector<std::string>;
		if(pos(x,y+1).isRvi()) list -> push_back(xy2str(x,y,1));
		if(pos(x+1,y).isRvi()) list -> push_back(xy2str(x,y,2));
		if(pos(x,y-1).isRvi()) list -> push_back(xy2str(x,y,3));
		if(pos(x-1,y).isRvi()) list -> push_back(xy2str(x,y,4));
		if(!(list -> empty())) maxList.push_back(list);
		else
			delete list;
	}

	for(unsigned i = 0; i < maxList.size();){
		for(unsigned j = 0; j < maxList[i] -> size();){
			*file << (*maxList[i])[j];
			if(++j < maxList[i] -> size())
				*file << " + ";
		}
		delete maxList[i];
		if(++i < maxList.size())
			*file << " + ";
		*file << std::endl;
	}

	*file << "Subject to" << std::endl;
	for(unsigned i = 0; i < _vNum; ++i){
		std::string rName,s1;
		int& x = _viaList[i].first;
		int& y = _viaList[i].second;
		printXY(rName,x,y,0); rName += ":";
		if(pos(x,y+1).isRvi()) printXY(s1,x,y,1);
		if(pos(x+1,y).isRvi()) printXY(s1,x,y,2);
		if(pos(x,y-1).isRvi()) printXY(s1,x,y,3);
		if(pos(x-1,y).isRvi()) printXY(s1,x,y,4);

		if(!s1.empty())
			*file << rName << " " << s1 << " <= 1" << std::endl;
	}
	int count = 1;
	for(unsigned i = 0; i < _rviList.size(); ++i){
		int& x = _rviList[i].first;
		int& y = _rviList[i].second;
		std::vector<std::string> cList;
		if(pos(x,y-1).isVia()) cList.push_back(xy2str(x,y-1,1));
		if(pos(x-1,y).isVia()) cList.push_back(xy2str(x-1,y,2));
		if(pos(x,y+1).isVia()) cList.push_back(xy2str(x,y+1,3));
		if(pos(x+1,y).isVia()) cList.push_back(xy2str(x+1,y,4));
		if(cList.size() > 1){
			*file << "C" << count << ":" << " " << gen1str(cList," + ") << " <= 1" << std::endl;
			++count;
		}
	}
	*file << "Bounds" << std::endl;
	*file << "Binary" << std::endl;
	for(unsigned i = 0; i < _vNum; ++i){
		int x = _viaList[i].first;
		int y = _viaList[i].second;
		std::vector<std::string> rList;
		if(pos(x,y+1).isRvi()) rList.push_back(xy2str(x,y,1));
		if(pos(x+1,y).isRvi()) rList.push_back(xy2str(x,y,2));
		if(pos(x,y-1).isRvi()) rList.push_back(xy2str(x,y,3));
		if(pos(x-1,y).isRvi()) rList.push_back(xy2str(x,y,4));
		if(!rList.empty()){
			*file << gen1str(rList," ") << std::endl;
		}
	}
	*file << "End" << std::endl;

}


//private aux. func

void vMap::printXY(std::string& str,int x,int y,int c = 0)
{
	if(!str.empty()) str += " + ";
	str += ("R_" + std::to_string(x) + "_" + std::to_string(y));
	if(c != 0)
		str += ("_" + std::to_string(c));

}

std::string vMap::xy2str(int x,int y,int c)
{
	std::string str;
	str += ("R_" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(c));
	return str;
}

std::string vMap::gen1str(std::vector<std::string>& list,std::string o)
{
	std::string str;
	for(unsigned i = 0; i < list.size(); ++i){
		if(!str.empty()) str += o;
		str += list[i];
	}
	return str;
}

Node& vMap::pos(int x,int y)
{
	return (_map[x+2][y+2]);
}

void vMap::lex(std::string& str, int&x, int& y)
{
	size_t pos = str.find_first_of(" ");
	std::string str1 = str.substr(0,pos);
	std::string str2 = str.substr(pos+1);
	x = std::stoi(str1);
	y = std::stoi(str2);
	return;
}

void vMap::clear()
{
	for(unsigned i = 0; i < _xDim + 2; ++i)
		delete[] _map[i];
	delete[] _map;

	delete[] _viaList;

}