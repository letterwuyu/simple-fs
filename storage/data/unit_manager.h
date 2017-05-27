#ifndef _UNIT_MANAGER_H__
#define _UNIT_MANAGER_H__

#include <unordered_map>

#include "unit.h"

class UnitManager {
public:
	typedef std::unordered_map<int, Unit*> UnitMap;
	UnitManager();
	~UnitManager();
	Unit* 			CreateUnit();
	bool   			DeleteUnit(int unit_id);
private:
	UnitMap unit_map_;
};
#endif //_UNIT_MANAGER_H__

