#ifndef _UNIT_MANAGER_H__
#define _UNIT_MANAGER_H__

#include <unordered_map>

#include "unit.h"

class UnitManager {
public:
	typedef std::unordered_map<long long, Unit*> UnitMap;
	UnitManager();
	~UnitManager();
	Unit* 			CreateUnit();
	bool   			DeleteUnit(long long  unit_id);
	void 			LoadUnitForMongoDB(void);
	Unit*           CreateUnit(long long unit_id);
private:
	UnitMap unit_map_;
};
#endif //_UNIT_MANAGER_H__

