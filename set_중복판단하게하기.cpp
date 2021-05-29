#include <set>
#include <map>
#include <iostream>
#include <string>

using namespace std;

class value
{
	public:
		int ma;
		std::string mb;
		int mc;
		value(int a, std::string b, int c) : ma(a), mb(b), mc(c){};

		bool operator < (const value& t) const
		{
			if (ma < t.ma || mb < t.mb || mc < t.mc)
				return true;
			else
				return false;
		}
		bool operator > (const value& t) const
		{
			if (ma > t.ma || mb > t.mb || mc > t.mc)
				return true;
			else
				return false;
		}
};

int main()
{
	std::set<value> temp;
	value temp2(10, "abc", 10);

	temp.insert(temp2);
	cout << temp.size() << endl;
	temp.insert(temp2);
	cout << temp.size() << endl;

	value temp3(10, "ssbc", 210);
	temp.insert(temp3);
	cout << temp.size() << endl;

	value temp5(-10, "ssbc", 210);
	temp.insert(temp5);
	cout << temp.size() << endl;

	value temp4(20, "ssbc", 3210);
	temp.insert(temp4);
	cout << temp.size() << endl;

	temp.insert(temp4);
	cout << temp.size() << endl;

	return (1);
}