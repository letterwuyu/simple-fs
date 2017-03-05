#ifndef _NET_THREAD_COMMON_H__
#define _NET_THREAD_COMMON_H__
#include <pthread.h>
#include <chrono>
class ThreadCommon
{
public:
	static const int THREAD_STATUS_NEW;
	static const int THREAD_STATUS_RUNNING;
	static const int THREAD_STATUS_EXIT;

	ThreadCommon();
	virtual ~ThreadCommon();
	virtual int Run() = 0;
	bool Start();
	void Join();
	void Join(const std::chrono::milliseconds& time);
	pThread_t getThreadId() const;
	int getStatus();
private:
	static void* thread_funcational(void* args);
private:
	pthread_t tid;
	int thread_status;
};
#endif /*_NET_THREAD_COMMON_H__
