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

int main()
{
	int client_fd;
	struct sockaddr_in sock;
	sock.sin_family = AF_INET;
	sock.sin_port = htons(8888);
	sock.sin_addr.s_addr = inet_addr("127.0.0.1");
	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	connect(client_fd, (struct sockaddr*)&sock, sizeof(sock));
	char buffer[] = "hello world";
/*	CS_ChunkIStream *pistream = (CS_ChunkIStream*)malloc(sizeof(CS_ChunkIStream) + strlen(buffer));
	pistream->header_.data_type_ = 1001;
	pistream->header_.data_size_ = sizeof(CS_ChunkIStream) + strlen(buffer) - sizeof(NetDataHeader);
	memcpy(pistream->chunk_data_, buffer, strlen(buffer));
	pistream->chunk_size_ = sizeof(buffer);
	send(client_fd, (char*)pistream, pistream->header_.data_size_ + sizeof(NetDataHeader), 0);
*/
	size_t size = sizeof(buffer);
	size_t pos = 0;
	struct CS_ChunkIStream* pcsistream = (struct CS_ChunkIStream*)malloc(sizeof(struct CS_ChunkIStream) + size);
    struct SC_ChunkIStream* pscistream = (struct SC_ChunkIStream*)malloc(sizeof(struct CS_ChunkIStream));
            pcsistream->header_.data_type_ = CS_CHUNK_ISTREAM; 
            pcsistream->header_.data_size_ = sizeof(struct CS_ChunkIStream) + size - sizeof(struct NetDataHeader);
            memcpy(pcsistream->chunk_data_, buffer, size);
            pcsistream->chunk_size_ = size;
            pcsistream->chunk_orgin_ = pos;
         //   int len = pcsistream->header_.data_size_ + sizeof(struct NetDataHeader);
           // int g  = 0;
             //      vfs_write(fpr, &len , sizeof(int), &g);
               //    filp_close(fpr, NULL);
                 //  set_fs(fsr);

            send(client_fd, (void*)pcsistream, pcsistream->header_.data_size_ + sizeof(struct NetDataHeader), 0);  
            recv(client_fd, pscistream, sizeof(struct SC_ChunkIStream), 0);

	getchar();
}










