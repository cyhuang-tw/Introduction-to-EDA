class myString;

class myString
{
public:
	myString(string str) { _str = str; }

private:
	string _str;
	bool _tail[2];
};