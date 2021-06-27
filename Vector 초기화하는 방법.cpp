#include <string>
#include <vector>
#include <iostream>
using namespace std;

void print_vector(vector<vector<int> > v)
{
	for (size_t i = 0; i < v.size(); i++)
	{	
		cout << i << "번째" << endl;
		for (size_t j = 0; j < v[i].size(); j++)
		{
			cout << v[i][j] << endl;
		}
		cout << "----------------" << endl;
	}
}

int main()
{
	// C++11 부터는 vector에 {}로 넣는 것이 가능하다.

	// std::vector<vector<int> > v(std::begin(x), std::end(x));
	// vector<vector<string>> v = {vector<string>(begin(arr[0]), end(arr[0])),
	//                           vector<string>(begin(arr[1]), end(arr[1]))};

	vector<vector<int> > briliant = { { 1, 12, 45, 134, 424 }, { 1, 12, 45, 134, 424 } }; // 이런 것도 됨

	// case 1 int arr[][2] = { {1,2}, {2,3}, {3,4}, {8,7}, {7,6} };
	// case 2 int arr[][2] = { {1,2}, {4,5}, {10,9}, {3,4} };
	// case 3 int arr[][2] = { {1,2}, {4,5}, {33333,33334}, {8,9} };
	// case 4
	int arr[][2] = { {2,1},{3,2},{4,3},{5,4},{6,5},{8,7},{7,6},{20,21},{18,19},{15,16},{16,17} };
	vector<vector<int> > v;
	for (size_t i = 0; i < 11; i++)
	{
		v.push_back(vector<int>(begin(arr[i]), end(arr[i])));
	}
	print_vector(v);
}