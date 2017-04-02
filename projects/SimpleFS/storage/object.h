#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <string>

class Object {
public:
	typedef size_t offset_type;
	typedef int32_t id_type;
	Object(std::string& name, id_type id);
	Object(const Object& object) = delete;
	Object(Object&& object) = delete;
	void SetName(std::string& name);
	void SetId(id_type id);
	void SetOffset(offset_type offset);
	const offset_type GetOffset() const;
	const std::string& GetName() const;
	const id_type GetId() const;
private:
	std::string name_;
	id_type id_;
	offset_type offset_;
};

#endif /* __OBJECT_H__ */
