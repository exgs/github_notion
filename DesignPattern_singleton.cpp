#pragma once

using namespace std;
#include <iostream>
class Singleton
{
	private:
		Singleton(){}
		static Singleton *inst;
	public:
		static Singleton *getInstance();
		void showMessage();
};
Singleton* Singleton::inst = nullptr;
Singleton* Singleton::getInstance()
{
	if (inst == nullptr)
		inst = new Singleton();
	return (inst);
}

void Singleton::showMessage()
{
	cout << "show message" << endl;
}

int main()
{
	Singleton::getInstance()->showMessage();
	Singleton::getInstance()->showMessage();
	Singleton::getInstance()->showMessage();
	return(0);
}