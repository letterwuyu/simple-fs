#ifndef _CXX_THREAD_H__
#define _CXX_THREAD_H__

#include <thread>
#include <future>

class CxxThread {
public:
	void Start(void);
	virtual void Run() = 0;
	void Join(void);
private:
	std::future<void> future;
};
#endif //_CXX_THREAD_H__
