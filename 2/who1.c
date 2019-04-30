#include<stdio.h>
#include<utmp.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

#define SHOWHOST
void show_info(struct utmp* utbufp);	//show information

int main(){
	struct utmp current_record;
	int utmpfd;
	int reclen = sizeof(current_record);
	if( ( utmpfd=open(UTMP_FILE, O_RDONLY)) == -1  ){ //UTMP_FILE in utmp.h
		perror(UTMP_FILE);
		exit(1);
	}
	
	while(read(utmpfd,&current_record,reclen) == reclen){ //read reclen bytes from current_record
		show_info(&current_record);
	}

	close(utmpfd);
	return 0;
}

void show_info(struct utmp *utbufp){
	if(utbufp->ut_type != USER_PROCESS)
		return;
	printf("%-8.8s",utbufp->ut_user);
	printf(" ");
	printf("%-8.8s",utbufp->ut_line);
	printf(" ");
       #ifdef SHOWHOST
	printf("(%s)",utbufp->ut_host);
       #endif
	printf("\n");	
}
