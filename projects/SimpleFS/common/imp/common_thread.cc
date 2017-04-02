#include "common_thread.h"
CommonThread::CommonThread():
	_tid(0), _thread_status(THREAD_STATUS_NEW) {}

CommonThread::~CommonThread() {}

bool CommonThread::Start()
{
	return pthread_create(&_tid, NULL, ThreadProxyFunc, this) == 0;
}

pthread_t CommonThread::getThreadId() const
{
	return _tid;
}

CommonThread::ThreadStatus CommonThread::getStatus() const
{
	return _thread_status;
}

void* CommonThread::ThreadProxyFunc(void *args)
{
	CommonThread *pThread = static_cast<CommonThread*>(args);
	pThread->_thread_status = THREAD_STATUS_RUNNING;
	pThread->Run();
}

void CommonThread::Join()
{
	if (_tid > 0)
	{
		pthread_join(_tid, NULL);
		_thread_status = THREAD_STATUS_EXIT;
	}
}
