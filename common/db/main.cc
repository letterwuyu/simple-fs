#include "mongodb_manager.h"
//#include "../imp/singleton.h"
//#include "../def/def.h"
int main()
{
	std::string db_name("test1"); 
	MongoDBManager manager(db_name);
	std::string volume_name("volume");
	manager.AddUnitForVolume(volume_name, 1);
	manager.AddUnitForVolume(volume_name, 2);
	std::vector<int> units;
	manager.GetUnitForVolume("volume", units);
}
