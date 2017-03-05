#include "ThreadCommom.h"

const int ThreadCommon::THREAD_STATUS_NEW = 0;
const int ThreadCommon::THREAD_STATUS_RUNNING = 1;
const int ThreadCommon::THREAD_STATUS_EXIT = -1;

void ThreadCommom::thread_functional(void* args)
{
	ThreadCommom *pThread = static_cast<ThreadCommom*>(args);
	pThread->thread_status = THREAD_STATUS_RUNNING;
	pThread->Run();
	return NULL;
}
ThreadCommom::ThreadCommon()
{
	tid = 0;
	thread_status = THREAD_STATUS_NEW;
}

ThreadCommon::~ThreadCommon() {}

bool ThreadCommon::Start()
{
	return pthread_create(&tid, NULL, thread_functional, this) == 0;
}

pthread_t ThreadCommon::getThreadId() const
{
	return tid;
}

int ThreadCommon::getStatus() const
{
	return thread_status;
}

void ThreadCommon::Join()
{
	if(tid > 0)
	{
		pthread_join(tid, NULL);
		thread_status = THREAD_STATUS_EXIT;
	}
}

void ThreadCommon::Join(const std::chrono::milliseconds& time)
{
	if(time == std::chrono::milliseconds(0))
	{
		Join();
	}
	else if(tid > 0)
	{
		while(thread_status != THREAD_STATUS_EXIT
		   && std::chrono::steady_clock::now() < time)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

}








