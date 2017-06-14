#ifndef _COMMON_THREAD_H_
#define _COMMON_THREAD_H_
#include <pthread.h>
class CommonThread
{
public:
	enum ThreadStatus
	{
		THREAD_STATUS_NEW = 0,
		THREAD_STATUS_RUNNING = 1,
		THREAD_STATUS_EXIT = -1,
	};
	CommonThread();
	virtual ~CommonThread();
	virtual void Run() = 0;
	bool Start();
	void Join();
	pthread_t getThreadId() const;
	ThreadStatus getStatus() const;
private:
	static void* ThreadProxyFunc(void *args);
private:
	pthread_t _tid;
	ThreadStatus _thread_status;
};
#endif // !_COMMON_THREAD_H_
