#ifndef __TRANSFER_H__
#define __TRANSFER_H__
#include <unistd.h>
#include <fcntl.h>
class Transfer {
public:
	enum SpliceFlag
	{
		Splice_Move = SPLICE_F_MOVE,
		Splice_NONBLOCK = SPLICE_F_NONBLOCK,
		SPlice_More = SPLICE_F_MORE,
		Splice_GIFT = SPLICE_F_GIFT
	}; 
	static ssize_t Splice(int src_fd, loff_t src_offset, int dst_fd, loff_t dst_offset, size_t size, unsigned int flag);
};
#endif /* __TRANSFER_H__ */
