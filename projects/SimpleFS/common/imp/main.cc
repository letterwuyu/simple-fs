#include "common_thread.h"
#include <iostream>
class MyThread :public CommonThread
{
	public:
	MyThread() : CommonThread() {}
	virtual void Run(){
		std::cout << "hello world" << std::endl;
	}
};

int main() {
	MyThread mt;
	mt.Start();
	mt.Join();
	while(1);
}
