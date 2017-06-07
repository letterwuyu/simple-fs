#ifndef _GC_NET_DEF_H__
#define _GC_NET_DEF_H__

enum GC_NetType {
	GC_CreateVirtualVolume = 2001,
	GC_DeleteVirtualVolume = 2002,
	GC_UpdateVirtualVolume = 2003,
	GC_ReadVirtualVolume = 2004,
	GC_CreateUser = 2005,
	GC_Connection = 2006,
	GC_VirtualVolumeSize = 2007,
};

#endif //_GC_NET_DEF_H__
