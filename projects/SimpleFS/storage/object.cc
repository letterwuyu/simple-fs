#include "object.h"

Object::Object(std::string& name, id_type id):
	name_(name), id_(id), offset_(0) {}

void Object::SetName(std::string& name)
{
	name_ = name;
}

void Object::SetId(Object::id_type id)
{
	id_ = id;
}

void Object::SetOffset(Object::offset_type offset)
{
	offset_ = offset;
}

const Object::offset_type Object::GetOffset() const
{
	return offset_;
}

const std::string& Object::GetName() const
{
	return name_;
}

const Object::id_type Object::GetId() const
{
	return id_;
}







