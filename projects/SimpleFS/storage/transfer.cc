#include "transfer.h"
 Transfer::return_type Transfer::spliceTransfer(int src_fd,
												Transfer::offset_type src_offset,
												int dst_fd,
												Transfer::offset_type dst_offset,
												Transfer::size_type size,
												Transfer::flag_type flag)
{
	int pipefd[2];
	pipe(pipefd);
	splice(src_fd, &src_offset, pipefd[1], NULL, size, flag);
	return splice(pipefd[0], NULL, dst_fd, &dst_offset, size, flag);
}
