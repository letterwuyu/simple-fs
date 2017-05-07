#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define SC_CHUNK_ISTREAM  1001
#define SC_CHUNK_OSTREAM  1002
#define CS_CHUNK_ISTREAM  2001
#define CS_CHUNK_OSTREAM  2002
#define MAX_NETPACK_SIZE  10000
int server_fd, client_fd;

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
    char   chunk_data_[0];
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
	char   chunk_data_[0];
};

struct CS_ChunkControl
{
    struct NetDataHeader header_;
};

#define MAX_CONTROL_SIZE 1024 * 1024 * 1024 * 8
#define MAX_BUFFER_SIZE 1024 * 8
static size_t control_seek = 0;
static size_t control_flag = 0;
int fd;
bool HandleNetPack(NetDataHeader* pDataHeader);


bool TcpDataSplit(const char* szRecNetData, int nRecSize)
{
	/**
	    对于szLastSaveData, nRemainSize,为了简单，本例子只
		作为静态变量使用，因此只限于一个socket的数据接收，
		假如要同时处理多个socket数据，请放在对应容器里保存
	*/
	
	printf("dddddd\n");
	static char szLastSaveData[MAX_NETPACK_SIZE];
	static int nRemainSize = 0;
	static bool bFirst = true;

	if (bFirst)
	{
		memset(szLastSaveData, 0, sizeof(szLastSaveData));
		bFirst = false;
	}

	/* 本次接收到的数据拼接到上次数据 */
	memcpy( (char*)(szLastSaveData+nRemainSize), szRecNetData, nRecSize );
	nRemainSize = nRecSize + nRemainSize;

	/* 强制转换成NetDataPack指针 */
	NetDataHeader* pDataHead = (NetDataHeader*)szLastSaveData;

	/**
	   核心算法 
	*/
	while ( nRemainSize >sizeof(NetDataHeader) &&
				nRemainSize >= pDataHead->data_size_ + sizeof(NetDataHeader) )
	{
			HandleNetPack(pDataHead);
			int  nRecObjectSize = sizeof(NetDataHeader) + pDataHead->data_size_;		//本次收到对象的大小
			nRemainSize -= nRecObjectSize ;				
			pDataHead = (NetDataHeader*)( (char*)pDataHead + nRecObjectSize );		//移动下一个对象头
	}
	
	/* 余下数据未能组成一个对象，先保存起来 */
	if (szLastSaveData != (char*)pDataHead)
	{
		memmove(szLastSaveData, (char*)pDataHead, nRemainSize);
		memset( (char*)( szLastSaveData+nRemainSize), 0, sizeof(szLastSaveData)-nRemainSize );
	}
	
	return true;
}


/**
    处理整理好的对象。
*/
bool HandleNetPack(NetDataHeader* pDataHeader)
{
	//处理数据包
	if  (pDataHeader->data_type_ == 2001)
	{
		printf("==========%d\n", CS_CHUNK_ISTREAM);
		CS_ChunkIStream *pcsistream = (CS_ChunkIStream*)pDataHeader;
		int fd_bak = open("storage_bak", O_RDWR, 0777);
		lseek(fd_bak, pcsistream->chunk_orgin_, SEEK_SET);
		write(fd_bak, pcsistream->chunk_data_, pcsistream->chunk_size_);
		close(fd_bak);
//		SC_ChunkIStream pscistream;
//		int ret = send(client_fd, (char*)&pscistream, sizeof(SC_ChunkIStream), 0);
	}
//	else if (pDataHeader->data_type_ == 2002)
//	{
//		printf("-----------------------------------------------------\n");	
//		printf("type = 1025");
//		CS_ChunkOStream* pcsostream = (CS_ChunkOStream*)pDataHeader;
//		int fd = open("storage", O_RDWR, 0777);
//        lseek(fd, pcsostream->chunk_orgin_, SEEK_SET);
//		SC_ChunkOStream* pscostream = (SC_ChunkOStream*)malloc(sizeof(SC_ChunkOStream) + pcsostream->chunk_size_);
//		pscostream->header_.data_type_ = SC_CHUNK_OSTREAM;
//		pscostream->header_.data_size_ = sizeof(SC_ChunkOStream) + pcsostream->chunk_size_ - sizeof(NetDataHeader);
////		pscostream->chunk_size_ = pcsostream->chunk_size_;
//        read(fd, pscostream->chunk_data_, pcsostream->chunk_size_);
//		int ret = send(client_fd, (char*)pscostream, pscostream->header_.data_size_ + sizeof(NetDataHeader), 0);
//		close(fd);
//		free(pscostream);
//		printf("------------%d\n", ret);
//	}
	if(pDataHeader->data_type_ == 1001)
	{
		CS_ChunkIStream* pistream = (CS_ChunkIStream*)pDataHeader;
		printf("%s\n", pistream->chunk_data_);
		printf("%lu\n",pistream->chunk_size_);
	}
	if(pDataHeader->data_type_ == 1003)
	{
		control_seek = 0;
		control_flag = (control_flag + 1) & 1;
		ftruncate(fd,0);
	}

	return true;
}


void Loop()
{
	if(control_flag)
	{
		fd = open("storage_log1", O_RDONLY, 0777);
	}
	else
	{
		fd = open("storage_log1", O_RDONLY, 0777);
	}
	char buffer[MAX_BUFFER_SIZE];
	lseek(fd, control_seek, SEEK_SET);
	while(true)
	{
		memset(buffer, 0, sizeof(buffer));
		size_t ret = read(fd, buffer, MAX_BUFFER_SIZE);
		if(ret == 0)
		{
			break;
		}
		control_seek += ret;
		TcpDataSplit(buffer, ret);
	}
}




int main()
{
/*	struct sockaddr_in sock;
	sock.sin_family = AF_INET;
	sock.sin_port = htons(8888);
	sock.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	bind(server_fd, (struct sockaddr*)&sock, sizeof(sock));
	listen(server_fd, 5);
	client_fd = accept(server_fd, NULL, NULL);
	printf("-- %lu--\n", sizeof(CS_ChunkControl));
	while(true)
	{
		client_fd = accept(server_fd, NULL, NULL);
		while(true)
		{
			printf("...\n");
			char buffer[1024];
			memset(buffer, 0, sizeof(buffer));
			int ret = recv(client_fd, buffer, 10000, 0);
			TcpDataSplit(buffer, ret);	
			printf("#####ret = %d %s\n", ret, buffer);
		}
	}
*/
	while(true)
	{
		sleep(2);
		Loop();
	}
}


















