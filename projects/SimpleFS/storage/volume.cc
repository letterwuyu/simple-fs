#include "volume.h"

Volume::Volume(Volume::id_type id):
	id_(id), objects_(std::map<Volume::object_id_type, Object>()), offset_(0) {}

const Volume::size_type Volume::GetSize()const
{
	return objects_.size();
}

const Volume::offset_type GetOffset() const
{
	return offset_;
}

void Volume::SetOffset(Volume::Offset_type offset)
{
	offset_ = offset;
}

void Volume::SetId(Volume::id_type id)
{
	id_ = id;
}

void Volume::EraseObject(Volume::object_id_type object_id)
{
	objects_.erase(object_id);
}

void Volume::InsertObject(Volume::object_id_type object_id, std::string& name)
{
	objects_.insert(std::make_pair(object_id, Object(object_id, name)));
}








