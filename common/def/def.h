#ifndef DEF_H
#define DEF_H

//package
#define DEFINE_MESSAGE_BEGIN(type)           \
	struct type##Message {                       \
		type##Message()                          \
		{                                         \
			Clear();                              \
			header_.data_type_ = type;          \
			header_.data_size_ = sizeof(this) - sizeof(net::NetDataHeader);    \
		}                                         \
		net::NetDataHeader  header_ ;               

#define DEFINE_MESSAGE_END };

#define PACKAGE_TYPE(type) type##Message

#define CONSTRUCT_MESSAGE(type) type##Message msg

#define UNPACKAGE(type) \
	SocketEvent*  pSocket = static_cast<SocketEvent*>( static_cast<struct bufferevent*>(pdev) ) \
	PACKAGE_TYPE(type) *  pPack = static_cast<PACKAGE_TYPE(type) * >(pData)

#define StaticHandle(type) static bool Process##type(void* event, void* data)
#define ClassHandle(cls, type) cls::Process##type(void* event, void* data)

#define GSingle(type) singleton<type>::intance()

#define GET_TYPE(type) type.header_.data_type_
#define GET_SIZE(type) type.header_.data_size_
#define GATE_UNPACK(type, data) PACKAGE_TYPE(type)* pack = static_cast<PACKAGE_TYPE(type) * >(data);
#define MAX_VOLUME_NAME 20

//log
#define LOGINFO  	LOGI
#define LOGWARN  	LOGW
#define LOGERROR 	LOGE
#define LOGALARM 	LOGA
#define LOGFATAL 	LOGF
#endif //DEF_H


//type

#define int32_t  sint32
#define int64_t  sint64
#define uint32_t uint32
#define uint64_t uint64

//handle
#define Client_Handle(type) ClientProcess_##type(void *pserv, void* pdev, void* pdata)
#define UN_CLIENT_PACKAGE(type) \
	SocketEvent*  pSocket = static_cast<SocketEvent*>(static_cast<struct bufferevent*>(psrv) ) \
    SocketEvent*  pSocket = static_cast<SocketEvent*>( static_cast<struct bufferevent*>(pdev) ) \
    PACKAGE_TYPE(type) *  pPack = static_cast<PACKAGE_TYPE(type) * >(pData)


//

#define MAX_COPY_NUM 2
