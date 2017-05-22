#ifndef _VOLUME_H_
#define _VOLUME_H_
#include <map>
#include <vector>
#include <string>
#include <future>
#include <sstream>
#include "unit.h"

class Volume {
public:
	typedef std::vector<std::tuple<int, int, void*, size_t>> comminute_type;
	Volume(const std::string& name, uint64 id);
	~Volume();
public:
	bool 		Write(size_t orgin, void* data, size_t count);
    bool 		Read(size_t orgin, void* data, size_t count);
	bool 		Delete(void);
	bool        Create(void);
private:
	bool 		ApplenUnit(void);
public:
    const 		std::string& GetName(void) const;
    uint64      GetId(void) const;

private:
	comminute_type Comminute(size_t orgin, void* data, size_t count);	
private:
	std::vector<Unit*> units_;
	std::string name_;
	uint64      id_;
};

#endif /* _VOLUME_H_ */










