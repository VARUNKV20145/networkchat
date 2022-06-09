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
	char server[100];
	struct sockaddr_in	 servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("172.16.51.191");
		
	int n, len;
	printf("Enter username:");
	char cname[50];
	gets(cname);
	sendto(sockfd, (const char *)cname, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	n = recvfrom(sockfd, (char *)server, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
	
	while(1){
	printf("You :");
	gets(hello);	
	sendto(sockfd, (const char *)hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	//printf("Hello message sent.\n");
			
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
	buffer[n] = '\0';
	printf("%s : %s\n",server, buffer);
	}
	close(sockfd);
	return 0;
}


