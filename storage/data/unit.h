#ifndef _UNIT_H_
#define _UNIT_H_
#include "..common/def/def.h"

class Unit {
public:
	static const size_t Size = 1024 * 1024 * 4;
	Unit(const std::string& name, uint64 id);
	~Unit();
	bool 		Write(size_t orign, void* buffer, size_t count);
	bool	 	Read(size_t orgin, void* buffer, size_t count);
	bool        Create();
	bool        Delete();
	uint64 		GetId();
	string      GetName();
private:
	std::string name_;
	uint64      id_;
	size_t      size_;
};

#endif /* _UNIT_H_ */
