#ifndef _UNIT_H__
#define _UNIT_H__

#include <string>

class Unit {
public:
	static const size_t Size = 1024 * 1024 * 4;
	Unit(const std::string& name, int id);
	~Unit();
	bool 		Write(size_t orign, void* buffer, size_t count);
	bool	 	Read(size_t orgin, void* buffer, size_t count);
	bool        Create();
	bool        Delete();
	int  		GetId();
	std::string      GetName();
private:
	std::string name_;
	int         id_;
	size_t      size_;
};

#endif /* _UNIT_H__ */
