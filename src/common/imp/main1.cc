#include "cxx_thread.h"
#include <iostream>
class A:public CxxThread
{
	void Run()
	{
		std::cout << "hello world" << std::endl;
	}
};

int main()
{
	A a;
	a.Start();
	a.Join();
}

