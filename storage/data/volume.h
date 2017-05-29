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
	Volume(const std::string& name, int id);
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
    int         GetId(void) const;

private:
	comminute_type Comminute(size_t orgin, char* data, size_t count);	
private:
	std::vector<Unit*> units_;
	std::string name_;
	int         id_;
};

#endif /* _VOLUME_H_ */











