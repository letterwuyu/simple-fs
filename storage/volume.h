#ifndef _VOLUME_H_
#define _VOLUME_H_
#include <map>
#include <vector>
#include <string>
#include <future>
#include <sstream>
#include "unit.h"

class Volume {
public:
	Volume() = delete;
private:
	typedef std::vector<std::tuple<int, int, void*, size_t>> comminute_type;
	comminute_type Comminute(size_t orgin, void* data, size_t count)
	{
		if(units_.size() * Unit::Size < orgin)
		{
			size_t diff = orgin - units.size() * Unit::Size;
			int num = diff / Unit::Size;
			while(--num)
			{
				CreateUnit();
			}
		}
		comminute_type coms;
		sint32 begin = orgin / Unit::Size;
		if(begin * Unit::Size + Unit::Size > orgin + count)
		{
			coms.push(make_tuple(begin, orgin - begin * Unit::Size, data, count));
		}
		else
		{
			size_t offset = begin * Unit::Size + Unit::Size - orgin;
			coms.push(make_tuple(begin, orgin - begin * Unit::Size, data, offset));
			coms.push(make_tuple(begin + 1, 0, data + offset, count - offset));	
		}
		return coms;
	}
	
	void CreateUnit()
	{	
		std::ostringstream os;
		os << AddUnitId();
		units_.push_back(os.str());
	}
	static void SetUnitId(uint64 i)
	{
		std::lock_guard<std::mutex> lk(mut_);
		UnitId = i;
	}
	static uint64 GetUnitId()
	{
		std::lock_guard<std::mutex> lk(mut_);
		return UnitId;
	}
	static uint64 AddUnitId()
	{
		std::lock_guard<std::mutex> lk(mut_);
		return UnitId++;
	}
public:
	void Write(size_t orgin, void* data, size_t count)
	{
		comminute_type comminutes = Comminute(orgin, data, count);
		for(comminute_type::iterator it = comminutes.begin();
			it != comminutes.end(); ++it)
		{
			vector[std::get<0>(*it)].Write(std::get<1>(*it), std::get<1>(*it), std::get<2>(*it), std::get<3>(*it));			
		}
	}
	void Read(size_t orgin, void* data, size_t count)
	{
		comminute_type comminutes = Comminute(orgin, data, count);
		for(comminute_type::iterator it = comminutes.begin();
            it != comminutes.end(); ++it)
        {
            vector[std::get<0>(*it)].Read(std::get<1>(*it), std::get<1>(*it), std::get<2>(*it), std::get<3>(*it));    
        }
	}

private:
	static uint64 UnitId;
	static std::mutex mut_;
	std::vector<Unit> units_;
};

#endif /* _VOLUME_H_ */











