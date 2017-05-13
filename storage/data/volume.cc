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
        	Unit* punit = GSingle(UnitManager).CreateUnit();
            Units_.push_back(punit);
			std::ostringstream vos(GSingle(DBManager).Get(std::to_string(id_)));
			if(vos.str().empty())
			{
				vos << punit->GetId();
			}
			else
			{
				vos << " " << punit->GetId();
			}
			GSingle(DBManager).Put(std::to_string(id_), vos.str());
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

bool Volume::Delete()
{
	for(size_t i = 0; i <units_.size(); ++i)
	{
		units_[i]->Delete();
	}
	GSingle(DBManager).Delete(name_);
	GSingle(DBManager).Delete(std::to_string(id_));
}

const std::string& Volume::GetName() const
{
	return name_;
}

uint64 Volume::GetId() const;
{
	return id_;
}
