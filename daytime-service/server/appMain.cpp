#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <time.h>

using namespace std;


#define PORT 12345

int main()
{
	int server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server < 0)
	{
		printf("error in socket.\n");
		return 0;
	}

	struct sockaddr_in address;
	bzero(&address, sizeof(sockaddr_in));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);
	
	if (bind(server, (sockaddr*)&address, sizeof(sockaddr_in)) < 0)
	{
		printf("error in bind.\n");
		close(server);
		return 0;
	}

	if (listen(server, 5) < 0)
	{
		printf("error in listen.\n");
		close(server);
		return 0;
	}


	for(;;)
	{
		vector<char> buffer(100);
		int client = accept(server, 0, 0);
		time_t ticks = time(NULL);
		sprintf(&buffer[0], "%.24s\r\n", ctime(&ticks));
		send(client, &buffer[0], strlen(&buffer[0]), 0);
		close(client);
	}
	close(server);

	return 0;

}
