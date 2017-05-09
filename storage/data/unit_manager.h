#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H
#include "unit.h"

class UnitManager {

public:
	typedef std::unordered_map<uint64, Unit*> UnitMap;
	UnitManager();
	~UnitManager();
	Unit* 			CreateUnit();
	bool   			DeleteUnit(uint64 unit_id);
private:
	UnitMap unit_map_;
};
#endif //UNIT_MANAGER_H
