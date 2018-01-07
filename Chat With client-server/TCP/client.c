#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define serverIp "127.0.0.1"
#define port 7891

int main()
{
	int clientSocket;
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(serverIp);

	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	addr_size = sizeof (serverAddr);
	while(1){
		if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size)==0){
			printf("Connection Established\n");
			break;
		}
		printf(". ");
		sleep(1);		
	}

	

	while(1){
		char data[1024];
		char buffer[1024];
		printf("Send: ");
		// scanf("%s", data);
		gets(data);
		send(clientSocket, data,1024,0);
		if(strcmp(data,"end") == 0)
			break;
		recv(clientSocket, buffer,1024,0);

		printf("Recieved:%s\n",buffer);
	}

	close(clientSocket);
	return 0;
}