#include "volume.h"
#include "../../common/def/def.h"
#include "../../common/imp/singleton.h"
#include "../../common/db/mongodb_cxx_manager.h"

#include "unit_manager.h"
using namespace imp;

Volume::Volume(const std::string& name, int id):
	name_(name), id_(id) {}

Volume::~Volume() {}

Volume::comminute_type Volume::Comminute(size_t orgin, char* data, size_t count)
{
	if(units_.size() * Unit::Size < orgin)
    {
    	size_t diff = orgin - units_.size() * Unit::Size;
        int num = diff / Unit::Size;
        while(--num)
        {
        	Unit* punit = GSingle(UnitManager)->CreateUnit();
            units_.push_back(punit);
			GSingle(MongoDBCXXManager)->GetDB().AddUnitForVolume(GetName(), punit->GetId());
        }
   	}
    comminute_type coms;
    int begin = orgin / Unit::Size;
    if(begin * Unit::Size + Unit::Size > orgin + count)
    {
    	coms.push_back(std::make_tuple(begin, orgin - begin * Unit::Size, static_cast<void*>(data), count));
    }
    else
    {
       	size_t offset = begin * Unit::Size + Unit::Size - orgin;
        coms.push_back(std::make_tuple(begin, orgin - begin * Unit::Size, static_cast<void*>(data), offset));
        coms.push_back(std::make_tuple(begin + 1, 0, static_cast<void*>(data + offset), count - offset)); 
    }
    return coms;
}

bool Volume::Write(size_t orgin, void* data, size_t count)
{	comminute_type comminutes = Comminute(orgin, static_cast<char*>(data), count);
	for(comminute_type::iterator it = comminutes.begin();
		it != comminutes.end(); ++it)
	{
			units_[std::get<0>(*it)]->Write(std::get<1>(*it), std::get<2>(*it), std::get<3>(*it));		
	}
	return true;
}

bool Volume::Read(size_t orgin, void* data, size_t count)
{
	comminute_type comminutes = Comminute(orgin, static_cast<char*>(data), count);
	for(comminute_type::iterator it = comminutes.begin();
    	it != comminutes.end(); ++it)
    {
    	units_[std::get<0>(*it)]->Read(std::get<1>(*it), std::get<2>(*it), std::get<3>(*it));    
    }
	return true;
}

bool Volume::Delete(void)
{
	for(size_t i = 0; i <units_.size(); ++i)
	{
		//将unit释放掉--将对应文件删除，从LevelDB中删除
		GSingle(MongoDBCXXManager)->GetDB().DelUnitForVolume(GetName(), units_[i]->GetId());	
		units_[i]->Delete();
	}
	return true;
}

const std::string& Volume::GetName(void) const
{
	return name_;
}

int Volume::GetId(void) const
{
	return id_;
}

bool Volume::ApplenUnit(void)
{
	Unit* punit = GSingle(UnitManager)->CreateUnit();
	if(nullptr == punit)
	{
		LogError("Volume::ApplenUnit nullptr == punit");
		return false;
	}
    units_.push_back(punit);
    //存入MongoDB
	GSingle(MongoDBCXXManager)->GetDB().AddUnitForVolume(name_, punit->GetId());
	return true;
}

bool Volume::Create(void)
{
	return ApplenUnit();
}















