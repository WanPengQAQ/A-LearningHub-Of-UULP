/*
 *	a client for remote ls
 */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<strings.h>
#include<unistd.h>
#include<string.h>

#define oops(msg) {perror(msg);exit(1);}
#define PORTNUM 15000

int main(int ac, char* av[])
{
	struct sockaddr_in servadd;
	struct hostent *hp;
	int sock_id, sock_fd;
	char buffer[BUFSIZ];
	int n_read = 0;

	if(ac != 3) exit(1);
	
	//step get socket
	sock_id = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_id == -1)
		oops("socket");
	//step connet to server
	bzero(&servadd, sizeof(servadd));
	hp = gethostbyname(av[1]);
	if(hp == NULL)
		oops(av[1]);
	bcopy(hp->h_addr, (struct sockaddr*)&servadd.sin_addr, hp->h_length);
	servadd.sin_port = htons(PORTNUM);
	servadd.sin_family = AF_INET;

	if(connect(sock_id, (struct sockaddr*)&servadd, sizeof(servadd)) != 0)
		oops("connet");
	//step 3 send message, then read results
	if(write(sock_id, av[2], strlen(av[2])) == -1)
		oops("write");
	if(write(sock_id, "\n", 1) == -1)
		oops("write2");
	
	while((n_read == read(sock_id, buffer, BUFSIZ)) > 0)
		if(write(1, buffer, n_read) == -1)
			oops("write3");
	close(sock_id);

	return 0;
}











