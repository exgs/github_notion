#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
void printVector(vector<T> &vec)
{
    for (const auto &item : vec) {
        cout << item << ", ";
    }
    cout << endl;
}

int main() {

    vector<int> arr4 = { 1, 12, 45, 134, 424 };
    vector<int> arr5 = { 41, 32, 15, 14, 99 };

	vector<int>::iterator it = arr4.begin();
	vector<int>::iterator it1 = arr4.begin();
	it1++;

	cout << "it: " << *it << endl;
	cout << "it1: " << *it1 << endl;
    printVector(arr4);
	cout << "---------------" << endl;
	iter_swap(it, it1);
	cout << "it: " << *it++ << endl;
	cout << "it1: " << *it1++ << endl;
	cout << "it: " << *it++ << endl;
	cout << "it1: " << *it1++ << endl;

    printVector(arr4);
    return EXIT_SUCCESS;
}