//#include "unp.h"
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_LINE 256

using namespace std;

int main(int argc, char** argv)
{
	vector<char> buffer(MAX_LINE);
	struct sockaddr_in serverAddress;

	if (argc < 2)
	{

		printf("Usage: daytime_client <IP address>\n");
		exit(0);
	}
	int serverSocket = -1;
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error\n");
		exit(0);
	}
	bzero(&serverAddress, sizeof(sockaddr_in));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(13);
	if (inet_pton(AF_INET, argv[1], &serverAddress.sin_addr) < 0)
	{
		printf("inet_pton error for %s\n", argv[1]);
		exit(0);
	}
	if (connect(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
	{
		printf("connect error\n");
		exit(0);
	}

	int n = 0;
	while((n = recv(serverSocket, &buffer[0], MAX_LINE, 0) ) > 0)
	{
		printf("current time is:%s\n", &buffer[0]);
	}
	if (n < 0)
	{
		printf("read error\n");
	}
	return 0;
}
