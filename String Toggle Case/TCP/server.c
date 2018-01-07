#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define serverIp "127.0.0.1"

void strMod(char* buffer){
	int i = 0;
	while (i < 1024) {
		if ('a' <= buffer[i] && buffer[i] <= 'z')
			buffer[i] = buffer[i] - ('a' - 'A');
		else if ('A' <= buffer[i] && buffer[i] <= 'Z')
			buffer[i] = buffer[i] + ('a' - 'A');
		i++;
	}
}

int main(){

	int welcomeSocket, newSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr (serverIp);

	memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

	bind(welcomeSocket,(struct sockaddr*) &serverAddr, sizeof(serverAddr));

	if (listen (welcomeSocket,5) == 0)
		printf("Listening\n");
	else
		printf("Error!!\n");

	addr_size = sizeof(serverStorage);
	newSocket = accept (welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

	recv(newSocket, buffer, 1024, 0);
	printf("\nData Recieved From Client : %s\n", buffer);
	strMod(buffer);
	send(newSocket, buffer, 1024, 0);

	close(newSocket);
	close(welcomeSocket);

}
