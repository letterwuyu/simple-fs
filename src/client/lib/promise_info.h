#ifndef _PROMISE_H__
#define _PROMISE_H__
struct PromiseInfo
{
	PromiseInfo() : data_(nullptr) {}
	PromiseInfo(void* data) : data_(data) {}
	void* data_;
};
#endif //_PORMISE_H__
