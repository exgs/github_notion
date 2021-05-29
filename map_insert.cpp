#include <map>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	std::map<int, std::string> temp;
	temp[1] = "abc";
	cout << temp[1] << endl;

	temp[1] = "second";
	cout << temp[1] << endl;
	cout << "----" << endl; 
	std::pair<int, std::string> pair(1, "eee");
	std::pair<std::map<int, std::string>::iterator,bool> ret = temp.insert(pair);
	cout << "map" << endl;
	cout << ret.first->first << " : " << ret.first->second << " |||| bool : " << ret.second << endl;
	cout << "---------" << endl;
	cout << "pair" << endl;
	cout << pair.first << " : " << pair.second << endl;
	return (1);
}