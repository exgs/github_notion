#include <vector>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	std::vector<int> temp;
	temp.push_back(1);
	temp.push_back(2);
	temp.push_back(3);
	temp.push_back(4);
	temp.push_back(5);
	temp.push_back(6);

	vector<int>::iterator it = temp.begin();
	it++;
	cout << *it << endl;
	cout << "===-=-=-=-===" << endl;
	temp.insert(it, 1000); //이터레이터 위치가 바뀜!!
	for (size_t i = 0; i < temp.size(); i++)
	{
		cout << temp[i] << endl;
	}
	cout << "===-=-=-=-===" << endl;
	// temp.push_back(2020);
	// temp.push_back(2021);
	while (it != temp.end())
	{
		cout << *it << endl;
		it++;
	}
	
	return (1);
}