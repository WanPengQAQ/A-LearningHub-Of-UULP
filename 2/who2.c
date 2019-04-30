#include<stdio.h>
#include<utmp.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

/*this "who" include buffer*/
#define SHOWHOST
void show_info(struct utmp* utbufp);	//show information

int main(){
	int fd;
	struct utmp *utmp_point;
	fd = utmp_open(UTMP_FILE);
	if(fd == -1){						//open utmp
		fprintf(stderr,"Cannot open %s\n",UTMP_FILE);
		exit(1);
	}	
	while((utmp_point=utmp_next())!= ((struct utmp*)NULL)){	//show utmp
		show_info(utmp_point);
	}
	utmp_close();						//close utmp
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
