using namespace std;

// 1. return값으로 가능한 값의 범위는 0 <= n <= 9
// 2. 단, 0으로 나누는 것은 제외

#include <string>
#include <set>
#include <iostream>


// set 라이브러리를 사용하지 않는다면, 배열에 넣는 방식도 생각 해볼 수 있을 것 같다.
// Array로 넣어야할 때, 대비한 함수
int isNumInArray(int *num_array, int num_array_size, int input)
{
	int i = 0;
	while (num_array[i] != -1)
	{
		if (num_array[i] == input)
		{
			return (-1);
		}
		i++;
	}
	return (i);
}
void InputArray(int *num_array, int n)
{
	while (n != 0)
	{
		int num = n % 10;
		int index;
		if ((index = isNumInArray(num_array, 10, num)) != -1)
		{
			num_array[index] = num;
		}
		n /= 10;
	}
}

void InputSet(std::set<int> &num_set, int n)
{
	while (n != 0)
	{
		int num = n % 10;
		num_set.insert(num);
		n /= 10;
	}
}

int solution(long long n)
{
	if (n <= 0)
		return (-1);

	int answer = 0;
	try
	{
		std::set<int> num_set;
		InputSet(num_set, n);
		std::set<int>::iterator it = num_set.begin();
		while (it != num_set.end())
		{
			if ((*it) == 0)
			{
				
			}
			else if (n % (*it) == 0)
			{
				answer++;
			}
			it++;
		}
	}
	catch(const std::exception& e)
	{
		// std::cerr << e.what() << '\n';
		return ((answer = -1));
	}
	return answer;
}

int main()
{
	
	for (size_t i = 0; i < 100009; i++)
	{
		if (solution(i) > 4)
			cout << "i: " << i << " | " << solution(i) << endl;
	}
	return (0);
}