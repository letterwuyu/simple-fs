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
			GSingle(MongoDBCXXManager).GetDB().AddUnitForVolume(GetName(), punit->GetId());
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

bool Volume::Delete(void)
{
	for(size_t i = 0; i <units_.size(); ++i)
	{
		//将unit释放掉--将对应文件删除，从LevelDB中删除
		units_[i]->Delete();
	}
	//将MongoDB中对应的volume清除
	return true;
}

const std::string& Volume::GetName(void) const
{
	return name_;
}

uint64 Volume::GetId(void) const;
{
	return id_;
}

bool Volume::ApplenUnit(void)
{
	Unit* punit = GSingle(UnitManager).CreateUnit();
	if(nullptr == punit)
	{
		LOGError("Volume::ApplenUnit nullptr == punit");
		return false;
	}
    Units_.push_back(punit);
    //存入MongoDB
	GSingle(MongoDBCXXManager).GetDB().AddUnitForVolume(name_, punit->GetId());
	return true;
}

bool Volume::Create(void)
{
	return ApplenUnit();
}















