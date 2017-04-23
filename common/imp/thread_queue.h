#ifndef _THREAD_QUEUE_H_
#define _TREEAD_QUEUE_H_
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

namespace imp {

template<typename T>
class ThreadQueue {
public:
	ThreadQueue() {}
	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mut_);
		data_cond_.wait(lk, [this]{return !data_queue_.empty();})
		value = std::move(*data_queue_.front());
		data_queue_.pop();	
	}
	
	bool try_pop(T& value)
	{
		std::lock_guard<std::mutex> lk(mut_);
		if(data_queue_.empty())
		{
			return false;
		}
		value = std::move(*data_queue_.front());
		data_queue_.pop();
		return true;
	}

	
private:
	mutable std::mutex mut_;
	std::queue<std::shared_ptr<T>> data_queue_;
	std::condition_variable data_cond_;
};

}


#endif // _THREAD_QUEUE_H_
