#ifndef __VOLUME_H__
#define __VOLUME_H__
#include "object.h"
#include <set>
#include <map>

class Volume {
public:
	typedef Object::offset_type offset_type;
	typedef int32_t id_type;
	typedef size_t size_type;
	typedef Object::id_type object_id_type;
	Volume(id_type id);
	const size_type GetSize() const;
	const offset_type GetOffset() const;
	void SetOffset(offset_type offset);
	void SetId(id_type id);
	void EraseObject(object_id_type object_id);
	void InsetObject(object_id_type object_id, std::string& object_name);
private:
	std::map<object_id_type, Object> objects_;
	offset_type offset_;
	id_type id_;
};

#endif /* __VOLUME_H__ */
