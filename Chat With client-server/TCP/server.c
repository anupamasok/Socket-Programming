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
	int welcomeSocket, newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	welcomeSocket = socket(PF_INET , SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(serverIp);

	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	if(listen(welcomeSocket,5)==0)
		printf("Listening\n");
	else
		printf("Error!!!\n");

	addr_size = sizeof (serverStorage);
	newSocket= accept(welcomeSocket, (struct sockaddr *)& serverStorage, &addr_size);
	while(1){
		char buffer[1024];
		
		recv(newSocket, buffer,1024,0);
		if(strcmp(buffer,"end") == 0)
			break;		
		printf("Recieved: %s\n",buffer);

		printf("Send: ");
		// scanf("%s", buffer);
		gets(buffer);
		send(newSocket, buffer,1024,0);
		if(strcmp(buffer,"end") == 0)
			break;			
	}
	
	close (welcomeSocket);
	close (newSocket);
	return 0;
}