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
		data_cond_.wait(lk, [this]{return !data_queue_.empty();});
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

	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_ptr<std::mutex> lk(mut_);
		data_cond_.wait(lk, [this]{return !data_queue_.empty();});
		std::shared_ptr<T> res = data_queue_.front();
		data_queue_.pop();
		return res;
	}
	
	std::shared_ptr<T> try_pop()
	{
		std::lock_guard<std::mutex> lk(mut_);
		if(data_queue_.empty())
		{
			return std::shared_ptr<T>();
		}
		std::shared_ptr<T> res = data_queue_.front();
		data_queue_.pop();
		return res;
	}

	void push(T new_value)
	{
		std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
		std::lock_guard<std::mutex> lk(mut_);
		data_queue_.push(data);
		data_cond_.notify_one();
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lk(mut_);
		return data_queue_.empty();
	}
private:
	mutable std::mutex mut_;
	std::queue<std::shared_ptr<T>> data_queue_;
	std::condition_variable data_cond_;
};

}


#endif // _THREAD_QUEUE_H_
