#include "volume.h"

Volume::Volume(const std::string& name, uint64 id):
	name_(name), id_(id) {}

Volume::comminute_type Volume::Comminute(size_t orgin, void* data, size_t count)
{
	if(units_.size() * Unit::Size < orgin)
    {
    	size_t diff = orgin - units.size() * Unit::Size;
        int num = diff / Unit::Size;
        while(--num)
        {
        	Unit* punit = CSingle(UnitManager).CreateUnit();
            Units_push_back(punit);
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

bool Volume::Write(size_t orgin, void* data, size_t count)
{	comminute_type comminutes = Comminute(orgin, data, count);
	for(comminute_type::iterator it = comminutes.begin();
		it != comminutes.end(); ++it)
	{
			units_[std::get<0>(*it)]->Write(std::get<1>(*it), std::get<1>(*it), std::get<2>(*it), std::get<3>(*it));		
	}
	return true;
}

bool Volume::bool Read(size_t orgin, void* data, size_t count)
{
	comminute_type comminutes = Comminute(orgin, data, count);
	for(comminute_type::iterator it = comminutes.begin();
    	it != comminutes.end(); ++it)
    {
    	units_[std::get<0>(*it)]->Read(std::get<1>(*it), std::get<1>(*it), std::get<2>(*it), std::get<3>(*it));    
    }
	return true;
}

const std::string& Volume::GetName() const
{
	return name_;
}

uint64 Volume::GetId() const;
{
	return id_;
}
