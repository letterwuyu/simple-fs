#include <linux/module.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/blkdev.h>

#include <linux/unistd.h>
#include <linux/fcntl.h>
#include <linux/string.h>

#include<linux/in.h>
#include<linux/inet.h>
#include<linux/socket.h>
#include<net/sock.h>

#include<linux/init.h>

static int sampleblk_major;
#define SAMPLEBLK_MINOR	1
#define MAX_CONTROL_SIZE 1024 * 1024 * 1024
static int sampleblk_sect_size = 512;
static int sampleblk_nsects = 10* 1024;

static size_t control_seek = 0;
static size_t control_flag = 0;

struct sampleblk_dev {
	int minor;
	spinlock_t lock;
	struct request_queue *queue;
	struct gendisk *disk;
	ssize_t size;
	void *data;
};

struct net_info
{
    struct socket *sock;
    struct sockaddr_in s_addr;
    unsigned short portnum;

    struct kvec vec;
    struct msghdr msg;

};

struct sampleblk_dev *sampleblk_dev = NULL;

struct net_info info;
char buffer_[10000];
// net package

#define SC_CHUNK_ISTREAM  1001
#define SC_CHUNK_OSTREAM  1002
#define CS_CHUNK_ISTREAM  2001
#define CS_CHUNK_OSTREAM  2002
#define CS_CHUNK_LOG      1003

struct NetDataHeader
{
    int32_t data_type_;
    int32_t data_size_;
};

struct CS_ChunkIStream
{
    struct NetDataHeader header_;
    size_t chunk_orgin_;
    size_t chunk_size_;
    char   chunk_data_[10240];
};

struct SC_ChunkIStream
{
	struct NetDataHeader header_;
	int32_t return_code_;
};

struct CS_ChunkOStream
{
	struct NetDataHeader header_;
	size_t chunk_orgin_;
	size_t chunk_size_;
};

struct SC_ChunkOStream
{
	struct NetDataHeader header_;
	size_t chunk_size_;
	char   chunk_data_[0];
};

struct CS_ChunkControl
{
	struct NetDataHeader header_;
};

struct CS_ChunkChange
{
	struct NetDataHeader header_;
};

//bool HandleNetPack(NetDataHeader* pDataHeader);
//
//
//bool TcpDataSplit(const char* szRecNetData, int nRecSize)
//{
//	/**
//	    对于szLastSaveData, nRemainSize,为了简单，本例子只
//		作为静态变量使用，因此只限于一个socket的数据接收，
//		假如要同时处理多个socket数据，请放在对应容器里保存
//	*/
//	printf("dddddd");
//	static char szLastSaveData[MAX_NETPACK_SIZE];
//	static int nRemainSize = 0;
//	static bool bFirst = true;
//
//	if (bFirst)
//	{
//		memset(szLastSaveData, 0, sizeof(szLastSaveData));
//		bFirst = false;
//	}
//
//	/* 本次接收到的数据拼接到上次数据 */
//	memcpy( (char*)(szLastSaveData+nRemainSize), szRecNetData, nRecSize );
//	nRemainSize = nRecSize + nRemainSize;
//
//	/* 强制转换成NetDataPack指针 */
//	NetDataHeader* pDataHead = (NetDataHeader*)szLastSaveData;
//
//	/**
//	   核心算法 
//	*/
//	while ( nRemainSize >sizeof(NetDataHeader) &&
//				nRemainSize >= pDataHead->data_size_ + sizeof(NetDataHeader) )
//	{
//			HandleNetPack(pDataHead);
//			int  nRecObjectSize = sizeof(NetDataHeader) + pDataHead->data_size_;		//本次收到对象的大小
//			nRemainSize -= nRecObjectSize ;			
//			pDataHead = (NetDataHeader*)( (char*)pDataHead + nRecObjectSize );		//移动下一个对象头
//	}
//	
//	/* 余下数据未能组成一个对象，先保存起来 */
//	if (szLastSaveData != (char*)pDataHead)
//	{
//		memmove(szLastSaveData, (char*)pDataHead, nRemainSize);
//		memset( (char*)( szLastSaveData+nRemainSize), 0, sizeof(szLastSaveData)-nRemainSize );
//	}
//	
//	return true;
//}
//
//
///**
//    处理整理好的对象。
//*/
//bool HandleNetPack(NetDataHeader* pDataHeader)
//{
//	//处理数据包
///*	if  (pDataHeader->data_type_ == 1024)
//	{
//		printf("type = 1024\n");
//		ReturnCode* pPeople = (ReturnCode*)pDataHeader;
//		if(pPeople->code_ == 2025)
//		{
//			IoChunkStream* pstream = (IoChunkStream*)malloc(sizeof(IoChunkStream) + pPeople->size_);
//			pstream->header_.data_type_ = RETURN_DATA_READ;
//			pstream->header_.data_size_ = sizeof(IoChunkStream) + pPeople->size_;
//			pstream->chunk_size_ = pPeople->size_;
//			int fd = open("storage", O_RDWR, 0777);
//			lseek(fd, pPeople->orgin_, SEEK_SET);
//			read(fd, pstream->chunk_data_, pPeople->size_);
//			close(fd);
//			send(client_fd, (char*)pstream, pstream->header_.data_size_, 0);
//			free(pstream);
//		}
//	}
//	else if (pDataHeader->data_type_ == 1025)
//	{
//		printf("type = 1025");
//		IoChunkStream* pstream = (IoChunkStream*)pDataHeader;
//		int fd = open("storage", O_RDWR, 0777);
//        lseek(fd, pstream->orgin_, SEEK_SET);
//        write(fd, pstream->chunk_data_, pstream->chunk_size_);
//		ReturnCode *pcode = (ReturnCode*)malloc(sizeof(ReturnCode));
//		send(client_fd, (char*)pcode, sizeof(pcode), 0);
//		free(pcode);
//	}
//*/
//	if(pDataHeader->data_type_ == 1001)
//	{
//		CS_ChunkIStream* pistream = (CS_ChunkIStream*)pDataHeader;
//		printf("%s\n", pistream->chunk_data_);
//		printf("%lu\n",pistream->chunk_size_);
//	}
//	return true;
//}
//
static int socket_create(void)
{
	int ret = 0;
    info.sock=(struct socket *)kmalloc(sizeof(struct socket),GFP_KERNEL);
    info.portnum = 8888;
    ret=sock_create_kern(AF_INET, SOCK_STREAM,0,&(info.sock));
    if(ret<0)
    {
        printk("client:socket create error!\n");
        return ret;
    }
    return 1;
}

static int connect(void)
{
	int ret = 0;
    memset(&(info.s_addr), 0, sizeof(info.s_addr));
    info.s_addr.sin_family = AF_INET;
    info.s_addr.sin_port = htons(info.portnum);
    info.s_addr.sin_addr.s_addr = in_aton("127.0.0.1"); /*server ip is 192.168.209.134*/
    ret=info.sock->ops->connect(info.sock,(struct sockaddr *)&(info.s_addr), sizeof((info.s_addr)),0);
    if(ret!=0)
    {
        printk("client:connect error!\n");
        return ret;
    }
	return 1;
}

static int send_buffer(void* buffer, size_t buffer_size)
{
	int ret = 0;
	memset(&(info.vec), 0, sizeof(info.vec));
    memset(&(info.msg), 0, sizeof(info.msg));
    info.vec.iov_base = buffer;
    info.vec.iov_len = buffer_size;
    ret=kernel_sendmsg(info.sock,&(info.msg),&(info.vec),1,buffer_size);
    if(ret<0)
    {
         printk("client: kernel_sendmsg error!\n");
         return ret;
    }
    else if(ret!=1024)
    {
         printk("client: ret!=1024");
    }
    return ret;
}
#if 0
static int recv_buffer(void* buffer, size_t buffer_size)
{
	int ret = 0;
	memset(&(info.vec), 0, sizeof(info.vec));
    memset(&(info.msg), 0, sizeof(info.msg));
    info.vec.iov_base = buffer;
    info.vec.iov_len = buffer_size;
	ret = kernel_recvmsg(info.sock,&(info.msg),&(info.vec),1,buffer_size,0);
	return ret;
}
#endif

static int sampleblk_handle_io(struct sampleblk_dev *sampleblk_dev,
		uint64_t pos, ssize_t size, void *buffer, int write)
{
	if (write)
		{
//		memcpy(sampleblk_dev->data + pos, buffer, size);
			struct CS_ChunkIStream* pcsistream = (struct CS_ChunkIStream*)vmalloc(sizeof(struct CS_ChunkIStream));
//           	struct CS_ChunkControl* pcscontrol = (struct CS_ChunkControl*)vmalloc(sizeof(struct CS_ChunkControl));

			struct file *fpr;

			mm_segment_t fsr;

			if(control_flag)
			{
				fpr = filp_open("/root/self/client/src/storage_log1", O_RDWR, 0777);
			}
			else
			{
				fpr = filp_open("/root/self/client/src/storage_log0", O_RDWR, 0777);
			}
			if(IS_ERR(fpr))
			{
				printk("create file error\n");
				return -1;
			}
			fsr = get_fs();
			set_fs(KERNEL_DS);

			#if 0 
			struct CS_ChunkIStream* pcsistream = (struct CS_ChunkIStream*)vmalloc(sizeof(struct CS_ChunkIStream) + size);
			struct CS_ChunkControl* pcscontrol = (struct CS_ChunkControl*)vmalloc(sizeof(struct CS_ChunkControl));
			struct SC_ChunkIStream* pscistream = (struct SC_ChunkIStream*)vmalloc(sizeof(struct CS_ChunkIStream));
			#endif
			memset(pcsistream, 0, sizeof(*pcsistream));
			pcsistream->header_.data_type_ = CS_CHUNK_ISTREAM;
			pcsistream->header_.data_size_ = sizeof(struct CS_ChunkIStream)  - sizeof(struct NetDataHeader);
			memcpy(pcsistream->chunk_data_, buffer, size);
			pcsistream->chunk_size_ = size;
			pcsistream->chunk_orgin_ = pos;
			memset(buffer_,0 , sizeof(buffer_));
			memcpy(buffer_, (char*)pcsistream, sizeof(struct CS_ChunkIStream));
		//	vfs_write(fpr, buffer_ , sizeof(*pcsistream), &control_seek);
			vfree(pcsistream);

			control_seek += (pcsistream->header_.data_size_ + sizeof(struct NetDataHeader));
			if(control_seek >= MAX_CONTROL_SIZE)
			{
				struct CS_ChunkControl* pcscontrol = (struct CS_ChunkControl*)vmalloc(sizeof(struct CS_ChunkControl));
				control_seek = 0;
				control_flag = (control_flag + 1) & 1;
	
				pcscontrol->header_.data_type_ = CS_CHUNK_LOG;
	            pcscontrol->header_.data_size_ = sizeof(struct CS_ChunkControl) - sizeof(struct NetDataHeader);
//				vfs_write(fpr, (char*)pcscontrol, sizeof(pcscontrol), &control_seek);
				control_seek += sizeof(pcscontrol);
				vfree(pcscontrol);
			}

  			filp_close(fpr, NULL);
			set_fs(fsr);
	
//			pcscontrol->header_.data_type_ = CS_CHUNK_LOG;
//			pcscontrol->header_.data_size_ = sizeof(struct CS_ChunkControl) - sizeof(struct NetDataHeader);
//			send_buffer((char*)pcscontrol, sizeof(pcscontrol));
//			send_buffer((char*)pcsistream, sizeof(struct CS_ChunkIStream) + size);
			#if 0
			send_buffer((char*)pcsistream, pcsistream->header_.data_size_ + sizeof(struct NetDataHeader));	
			recv_buffer(pscistream, sizeof(struct SC_ChunkIStream));
			#endif
//			vfree(pcsistream);
	
			struct file *fps;
            mm_segment_t fss;
	

			fps = filp_open("/root/self/client/src/storage", O_RDWR, 0777);
			if(IS_ERR(fps))
            {
                printk("create file error\n");
                return -1; 
            }
            fss = get_fs();
            set_fs(KERNEL_DS);
			vfs_write(fps, buffer, size, &pos);
			filp_close(fps, NULL);
            set_fs(fss);		
		}
	else
		{
			//memcpy(buffer, sampleblk_dev->data + pos, size);
			struct file *fpw;
            mm_segment_t fsw;
			fpw = filp_open("/root/self/client/src/storage", O_RDWR, 0777);
			if(IS_ERR(fpw))
			{
				printk("create file error\n");
				return -1;
			}
			fsw = get_fs();
			set_fs(KERNEL_DS);
			vfs_read(fpw, buffer, size, &pos);
			filp_close(fpw, NULL);
			set_fs(fsw);
			
		//	struct CS_ChunkOStream* pcsostream = (struct CS_ChunkOStream*)vmalloc(sizeof(struct CS_ChunkOStream));
		//	struct SC_ChunkOStream* pscostream = (struct SC_ChunkOStream*)vmalloc(sizeof(struct SC_ChunkOStream) + size);
		//	pcsostream->header_.data_type_ = CS_CHUNK_OSTREAM;
		//	pcsostream->header_.data_size_ = sizeof(struct CS_ChunkOStream) - sizeof(struct NetDataHeader);
		//	pcsostream->chunk_orgin_ = pos;
		//	pcsostream->chunk_size_ = size;
		//	send_buffer((void*)pcsostream, pcsostream->header_.data_size_);
		//	//recv_buffer(pscostream, sizeof(struct SC_ChunkOStream) + size);
		//	memcpy(buffer, (struct SC_ChunkOStream*)pscostream->chunk_data_, size);
		//	vfree(pcsostream);
		//	vfree(pscostream);
		}
	return 0;
}

static void sampleblk_request(struct request_queue *q)
{
	struct request *rq = NULL;
	int rv = 0;
	uint64_t
	 pos = 0;
	ssize_t size = 0;
	struct bio_vec* bvec;
	struct req_iterator iter;
	void *kaddr = NULL;

	while ((rq = blk_fetch_request(q)) != NULL) {
		spin_unlock_irq(q->queue_lock);

		if (rq->cmd_type != REQ_TYPE_FS) {
			rv = -EIO;
			goto skip;
		}

		BUG_ON(sampleblk_dev != rq->rq_disk->private_data);

		pos = blk_rq_pos(rq) * sampleblk_sect_size;
		size = blk_rq_bytes(rq);
		if ((pos + size > sampleblk_dev->size)) {
			pr_crit("sampleblk: Beyond-end write (%llu %zx)\n",
				pos, size);
			rv = -EIO;
			goto skip;
		}

		rq_for_each_segment(bvec, rq, iter) {
			kaddr = kmap(bvec->bv_page);

			rv = sampleblk_handle_io(sampleblk_dev, pos,
				bvec->bv_len, kaddr + bvec->bv_offset,
				rq_data_dir(rq));
			if (rv < 0)
				goto skip;

			pos += bvec->bv_len;
			kunmap(bvec->bv_page);
		}
skip:

		blk_end_request_all(rq, rv);

		spin_lock_irq(q->queue_lock);
	}
}

static int sampleblk_ioctl(struct block_device *bdev, fmode_t mode,
			unsigned command, unsigned long argument)
{
	return 0;
}

static int sampleblk_open(struct block_device *bdev, fmode_t mode)
{
	return 0;
}

static void sampleblk_release(struct gendisk *disk, fmode_t mode)
{
}

static const struct block_device_operations sampleblk_fops = {
	.owner = THIS_MODULE,
	.open = sampleblk_open,
	.release = sampleblk_release,
	.ioctl = sampleblk_ioctl,
};

static int sampleblk_alloc(int minor)
{
	struct gendisk *disk;
	int rv = 0;

	sampleblk_dev = kzalloc(sizeof(struct sampleblk_dev), GFP_KERNEL);
	if (!sampleblk_dev) {
		rv = -ENOMEM;
		goto fail;
	}

	sampleblk_dev->size = sampleblk_sect_size * sampleblk_nsects;
	sampleblk_dev->data = vmalloc(sampleblk_dev->size);
	if (!sampleblk_dev->data) {
		rv = -ENOMEM;
		goto fail_dev;
	}
	sampleblk_dev->minor = minor;

	spin_lock_init(&sampleblk_dev->lock);
	sampleblk_dev->queue = blk_init_queue(sampleblk_request,
	    &sampleblk_dev->lock);
	if (!sampleblk_dev->queue) {
		rv = -ENOMEM;
		goto fail_data;
	}

	disk = alloc_disk(minor);
	if (!disk) {
		rv = -ENOMEM;
		goto fail_queue;
	}
	sampleblk_dev->disk = disk;

	disk->major = sampleblk_major;
	disk->first_minor = minor;
	disk->fops = &sampleblk_fops;
	disk->private_data = sampleblk_dev;
	disk->queue = sampleblk_dev->queue;
	sprintf(disk->disk_name, "sampleblk%d", minor);
	set_capacity(disk, sampleblk_nsects);
	add_disk(disk);

	return 0;

fail_queue:
	blk_cleanup_queue(sampleblk_dev->queue);
fail_data:
	vfree(sampleblk_dev->data);
fail_dev:
	kfree(sampleblk_dev);
fail:
	return rv;
}

static void sampleblk_free(struct sampleblk_dev *sampleblk_dev)
{
	del_gendisk(sampleblk_dev->disk);
	blk_cleanup_queue(sampleblk_dev->queue);
	put_disk(sampleblk_dev->disk);
	vfree(sampleblk_dev->data);
	kfree(sampleblk_dev);
}

static int __init sampleblk_init(void)
{
	int rv = 0;

	sampleblk_major = register_blkdev(0, "sampleblk");
	if (sampleblk_major < 0)
		return sampleblk_major;

	rv = sampleblk_alloc(SAMPLEBLK_MINOR);
	if (rv < 0)
		pr_info("sampleblk: disk allocation failed with %d\n", rv);

	pr_info("sampleblk: module loaded\n");

//	socket_create();
//	connect();
	return 0;
}

static void __exit sampleblk_exit(void)
{
	sampleblk_free(sampleblk_dev);
	unregister_blkdev(sampleblk_major, "sampleblk");

	pr_info("sampleblk: module unloaded\n");
}

module_init(sampleblk_init);
module_exit(sampleblk_exit);
MODULE_LICENSE("GPL");

