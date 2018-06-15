#include <vector>

using namespace std;

class myTree;
class Node;

class myTree
{
public:
	myTree() { init(); }
	~myTree() { reset(); }

private:
	void init();
	void reset();

	Node* _root;
};

class Node
{
	friend class myTree;
	Node() { init(); }
	~Node() { reset(); }

	void init();
	void reset();
	string _data;
	vector<Node*> _child;


};