#include "transfer.h"
 Transfer::return_type Transfer::spliceTransfer(int src_fd,
												loff_t src_offset,
												int dst_fd,
												loff_t dst_offset,
												size_t size,
												unsigned int flag)
{
	int pipefd[2];
	pipe(pipefd);
	splice(src_fd, &src_offset, pipefd[1], NULL, size, flag);
	return splice(pipefd[0], NULL, dst_fd, &dst_offset, size, flag);
}
