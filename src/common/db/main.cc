#include "mongodb_cxx_manager.h"
//#include "../imp/singleton.h"
//#include "../def/def.h"
int main()
{
	std::string db_name("test1"); 
	MongoDBCXXManager manager;
	std::string volume_name("volume");
	manager.GetDB().AddUnitForVolume(volume_name, 1);
	manager.GetDB().AddUnitForVolume(volume_name, 2);
	std::vector<int> units;
	manager.GetDB().GetUnitForVolume("volume", units);
}
