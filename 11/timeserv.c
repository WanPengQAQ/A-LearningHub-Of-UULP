#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<strings.h>

#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg) {perror(msg);exit(1);}

int main(int ac, char* av[])
{
	int sock_id, sock_fd;
	struct sockaddr_in saddr;
	struct hostent *hp;
	char hostname[HOSTLEN];
	FILE* sock_fp;	
	time_t thetime;

	//step 1
	sock_id =socket(PF_INET, SOCK_STREAM, 0);
		if(sock_id == -1)
			oops("socket");
	//step 2
	bzero((void*)&saddr, sizeof(saddr));
	gethostname(hostname, HOSTLEN);

	printf("hostname:%s\n", hostname);

	hp = gethostbyname(hostname);

	bcopy((void*)hp->h_addr, (void*)&saddr.sin_addr, hp->h_length);
	saddr.sin_port = htons(PORTNUM);
	saddr.sin_family = AF_INET;
	
	if(bind(sock_id, (struct sockaddr*)&saddr, sizeof(saddr)) != 0){
		//bind:cannot assign requested address 
		//  /etc/hosts add hoetname
		oops("bind");
	}
	//step 3
	if(listen(sock_id, 1) != 0)
		oops("listen");
	//main loop:
	while(1){
		sock_fd = accept(sock_id, NULL, NULL);
		printf("Wow! got a call!\n");
		if(sock_fd == -1)
			oops("accept");
			
		sock_fp = fdopen(sock_fd, "w");
		if(sock_fp == NULL)
			oops("fdopen");
		
		thetime = time(NULL);
		fprintf(sock_fp,"The time here is ..");
		fprintf(sock_fp,"%s",ctime(&thetime));
		fclose(sock_fp);
	}
	
}












