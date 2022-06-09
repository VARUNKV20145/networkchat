// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	 8080
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char hello[100];
	char client_name[100];
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		
	int len, n;
	
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
			MSG_WAITALL, ( struct sockaddr *) &cliaddr,
			&len);
	buffer[n] = '\0';
	printf("username: %s\n", buffer);
	//client_name = buffer;
	strcpy(client_name, buffer);
	
	printf("Enter your name: ");
	gets(hello);

		sendto(sockfd, (const char *)hello, strlen(hello),
	MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
		len);
	
	
	len = sizeof(cliaddr); //len is value/result
	
	while(1) {

	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
	buffer[n] = '\0';
	printf("%s: %s\n", client_name, buffer);
	printf("Waiting for message: ");
	gets(hello);
	sendto(sockfd, (const char *)hello, strlen(hello),
	MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
		len);
	printf("#\n");
	}

		
	return 0;
}


