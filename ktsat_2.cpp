#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
void print_vector(vector<vector<int> > v);

void SetAnswer(vector<int> &answer, vector <vector<int> > v_dots)
{
	if (v_dots.size() == 0)
		return ;
	pair<int, int> before;
	before.first = v_dots[0][0];
	before.second = v_dots[0][1];
	int start_dot = before.first;
	pair<int, int> cur = before;
	for (size_t i = 1; i < v_dots.size(); i++)
	{
		cur.first = v_dots[i][0]; cur.second = v_dots[i][1];
		if (before.second == cur.first)
		{
			before = cur;
		}
		else
		{
			answer.push_back(start_dot);
			answer.push_back(before.second);
			before = cur;
			start_dot = cur.first;
		}
	}
	answer.push_back(start_dot);
	answer.push_back(cur.second);
}

vector<int> solution(vector<vector<int> > paths)
{
	vector<int> answer;
	vector <vector<int> > LtoR;
	vector <vector<int> > RtoL;
	for (size_t i = 0; i < paths.size(); i++)
	{
		if (paths[i][0] < paths[i][1])
		{
			LtoR.push_back(paths[i]);
		}
		else
		{
			RtoL.push_back(paths[i]);
		}
	}
	sort(LtoR.begin(), LtoR.end());
	sort(RtoL.rbegin(), RtoL.rend());
	//STUB
	// print_vector(LtoR);
	// cout << "=============" << endl;
	// print_vector(RtoL);

	SetAnswer(answer, LtoR);
	SetAnswer(answer, RtoL);
	return answer;
}

int main()
{

	// case 1
	// int arr[][2] = { {1,2}, {2,3}, {3,4}, {8,7}, {7,6} };
	
	// case 2
	// int arr[][2] = { {1,2}, {4,5}, {10,9}, {3,4} };

	// case 3
	// int arr[][2] = { {1,2}, {4,5}, {33333,33334}, {8,9} };

	// case 3
	int arr[][2] = { {2,1},{3,2},{4,3},{5,4},{6,5},{8,7},{7,6},{20,21},{18,19},{15,16},{16,17} };
	// std::vector<vector<int> > v(std::begin(x), std::end(x));
	// vector<vector<string>> v = {vector<string>(begin(arr[0]), end(arr[0])),
    //                           vector<string>(begin(arr[1]), end(arr[1]))};
	vector<vector<int> > v;
	for (size_t i = 0; i < 11; i++)
	{
		v.push_back(std::vector<int>(begin(arr[i]), end(arr[i])));
	}

	try
	{
		vector<int> temp = solution(v);
		for (size_t i = 0; i < temp.size(); i += 2)
		{
			cout << temp[i] << " : " << temp[i + 1] << endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}

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