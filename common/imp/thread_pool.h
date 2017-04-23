#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#include <thread>
#include <memory>
#include <atomic>
#include <future>
#include <functional>
#include "thread_queue.h"
#include <iostream>
namespace imp {

class FunctionWrapper {
private:
	struct ImplBase {
		virtual void call() = 0;
		virtual ~ImplBase() {}
	};

	std::unique_ptr<ImplBase> impl_;

	template<typename F>
	struct ImplType : ImplBase {
		F f_;
		ImplType(F&& f) : f_(std::move(f)) {}
		virtual void call() override { f_(); }
	};

public:
	template<typename F>
	FunctionWrapper(F&& f) : impl_(new ImplType<F>(std::move(f))) {}
	
	void operator()() { impl_->call(); }
	FunctionWrapper() = default;
	FunctionWrapper(FunctionWrapper&& other) : impl_(std::move(other.impl_)) {}
	FunctionWrapper& operator=(FunctionWrapper&& other)
	{
		impl_ = std::move(other.impl_);
		return *this;
	}
	
	FunctionWrapper(const FunctionWrapper&) = delete;
	FunctionWrapper(FunctionWrapper&) = delete;
	FunctionWrapper& operator=(const FunctionWrapper&) = delete;
};

class JoinThreads {
public:
	explicit JoinThreads(std::vector<std::thread>& threads) : threads_(threads) {}
	~JoinThreads()
	{
		for(unsigned long i = 0; i < threads_.size(); ++i)
		{
			if(threads_[i].joinable())
			{
				threads_[i].join();
			}
		}
	}
private:
	std::vector<std::thread>& threads_;
};

class ThreadPool {
public:
	ThreadPool(): done_(false), joiner_(threads_)
	{
		const unsigned thread_count = std::thread::hardware_concurrency();
		try
		{
			for(unsigned i = 0; i < thread_count; ++i)
			{
				threads_.push_back(std::thread(&ThreadPool::WorkThread, this));
			}
		}
		catch(...)
		{ 
			done_ = true;
			throw;
		} 
	}

	~ThreadPool()
	{  
		done_ = true;
	}

	template<typename FunctionType>
	std::future<typename std::result_of<FunctionType()>::type>
	Submit(FunctionType f)
	{
		typedef typename std::result_of<FunctionType()>::type result_type;
		std::packaged_task<result_type()> task(f);
		std::future<result_type> res(task.get_future());
		if(local_work_queue_)
		{
			local_work_queue_->push(std::move(task));
		}
		else
		{
			pool_work_queue_.push(std::move(task));
		}
		return res;
	}
	
	void RunPendingTask()
	{
		FunctionWrapper task;
		if(local_work_queue_ && !local_work_queue_->empty())
		{
			task = std::move(local_work_queue_->front());
			local_work_queue_->pop();
			task();
		}
		else if(pool_work_queue_.try_pop(task))
		{
			task();
		}
		else
		{
			std::this_thread::yield();
		}
	}
private:
	void WorkThread()
	{  
		local_work_queue_.reset(new LocalQueueType);
		while(!done_)
		{
			RunPendingTask();
		}
	}
	
public:
	typedef std::queue<FunctionWrapper> LocalQueueType;
private:
	ThreadQueue<FunctionWrapper> pool_work_queue_;
	static thread_local std::unique_ptr<LocalQueueType> local_work_queue_;
	std::atomic_bool done_;
	std::vector<std::thread> threads_;
	JoinThreads joiner_;
};
thread_local std::unique_ptr<ThreadPool::LocalQueueType> ThreadPool::local_work_queue_;

}
#endif //_THREAD_POOL_H_
























