#ifndef DEF_H
#define DEF_H

#define DEFINE_MESSAGE_BEGIN(type)           \
	struct type##Message {                       \
		type##Message()                          \
		{                                         \
			Clear();                              \
			header_.data_type_ = type;          \
			header_.data_size_ = sizeof(this);    \
		}                                         \
		net::NetDataHeader  header_ ;               

#define DEFINE_MESSAGE_END };

#define PACKAGE_TYPE(type) type##Message

#define CONSTRUCT_MESSAGE(type) type##Message Msg

#define UNPACKAGE(type) \
	SocketEvent*  pSocket = static_cast<SocketEvent*>( static_cast<struct bufferevent*>(dev) ) \
	PACKAGE_TYPE(type) *  pPack = static_cast<PACKAGE_TYPE(type) * >(pData)

#define GET_TYPE(type) type.header_.data_type_
#define GET_SIZE(type) type.header_.data_size_
#define HANDLE(type) Handle##type(void* dev, void* pData)
#define STATIC_HANDLE(type) static HANDLE(type);
#endif //DEF_H

