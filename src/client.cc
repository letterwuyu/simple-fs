#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

int main(int argc, char **argv) {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct hostent *server = gethostbyname("127.0.0.1");
	if(server == NULL) {
		printf("ERROR, no such host\n");
		exit(0);
	}
	
	struct sockaddr_in serv_addr;
	memset((char*)&serv_addr, 0, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	memcpy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(8888);
	if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) <0) {
		printf("error connect %d\n", errno);
		exit(0);
	}
	char buf[1024] = {0};
	strcpy(buf, "hello world");
	int n = write(sockfd, buf, sizeof(buf));
	buf[n] = '\0';
	printf("%s\n", buf);
	close(sockfd);
	return 0;	
}


















