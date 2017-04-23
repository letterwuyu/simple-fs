#include "thread_pool.h"
#include <iostream>

void fun1() {
	std::cout << "hello" << std::endl;
}

void fun2() {
	std::cout << "world" << std::endl;
}

int main()
{
	imp::ThreadPool tp;
	tp.Submit(fun1);	
	tp.Submit(fun2);
}
