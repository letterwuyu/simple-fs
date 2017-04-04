#ifndef __TRANSFER_H__
#define __TRANSFER_H__
#include <unistd.h>
#include <fcntl.h>
class Transfer {
public:
	typedef loff_t offset_type;
	typedef size_t size_type;
	typedef unsigned int flag_type;
	typedef ssize_t return_type;
	enum SpliceFlag
	{
		Splice_Move = SPLICE_F_MOVE,
		Splice_NONBLOCK = SPLICE_F_NONBLOCK,
		SPlice_More = SPLICE_F_MORE,
		Splice_GIFT = SPLICE_F_GIFT
	}; 
	static return_type spliceTransfer(int src_fd, 
									  offset_type src_offset,
									  int dst_fd,
									  offset_type dst_offset,
									  size_type size,
									  flag_type flag);
};
#endif /* __TRANSFER_H__ */
