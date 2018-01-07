#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define serverIp "127.0.0.1"

void getData(char* data){
	printf("Enter The Data You Want to Send: \n");
	scanf("%[^\n]s",data);	
}

int main(){

	int clientSocket;
	char buffer[1024],data[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr(serverIp);

	memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

	addr_size = sizeof (serverAddr);
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

	getData(data);
	while(1){
		if(send(clientSocket,data,1024,0)){
			printf("Connection Established!!\n");
			break;
		}
	}
	

	recv(clientSocket,buffer,1024,0);
	printf("\nData Recieved From Server : %s\n", buffer);
	
	close(clientSocket);
	return 0;
}