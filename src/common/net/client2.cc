#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <iostream>
#include "package_analysis.h"
#include "test_message.h"
#include <stdint.h>
#include <string.h>

using namespace net;
int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sockadd;
	sockadd.sin_family = AF_INET;
	sockadd.sin_port = htons(8889);
	sockadd.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sockfd, reinterpret_cast<struct sockaddr*>(&sockadd), sizeof(sockadd));
	listen(sockfd, 10);
	int clientfd = accept(sockfd, NULL, NULL);
	/*
	Message msg;
	msg.header_.data_type_ = 1;
	msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
	*/
	size_t size = sizeof(Message)+sizeof(char)*12;
	Message* msg = (Message*)malloc(size);
	msg->header_.data_type_ = 1;
	msg->header_.data_size_ = size - sizeof(NetDataHeader);
	msg->s = 11;
	std::cout << "s:" << msg->s;
	strcpy(msg->a, "hello world");	
	printf("============================\n");
	send(clientfd, msg, size, 0);	
//	char buffer[12];
//	recv(clientfd, buffer, 12, 0);
//	std::cout << buffer << std::endl;
}








