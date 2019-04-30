#include<stdio.h>
#include<stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE* fp);
int see_more(FILE* fp);

int main(int ac, char* av[])
{
	FILE* fp;
	if(ac == 1){		//only more2 in command  
		do_more(stdin); 
	} else {			//indicate the specific path in command such as "more2 /etc/profile"
		int i;
		for(i = 1; i < ac; i++){
			if((fp = fopen(av[i],"r"))!=NULL){
			//	printf("open %s succeed\n",av[i]);
				do_more(fp);
				see_more(fp);
			}else{
			//	printf("open %s faliure\n",av[i]);
				exit(1);//failure
			}
		}
	}
	return 0;
}

void do_more(FILE* fp) //read PAGELEN lines, and call see_more()
{
	char line[LINELEN];
	int num_of_lines = 0;
	int replay;
	FILE* fp_tty;
	fp_tty = fopen("/dev/tty","r");
	if(fp_tty==NULL){
	//	printf("open tty failure in do_more()\n");
		exit(1);
	}
	
	while(fgets(line,LINELEN,fp)){
		if(num_of_lines == PAGELEN){ //ask weather continure
			replay = see_more(fp_tty);
			if(replay == 0)
				break;
			num_of_lines -= replay;
		}
		if(fputs(line,stdout) == EOF)
			exit(1);		//failure
		num_of_lines++;
	}
}

int see_more(FILE* fp)
{
	int c;
	printf("\033[7m more?\033[m");
	FILE* fp_tty;
	fp_tty = fopen("/dev/tty","r");
	if(fp_tty == NULL){
	//	printf("open tty failure in see_more()\n");
		return 0;
	}
	while((c=getc(fp_tty)) != EOF ){
		if(c == 'q')
			return 0;
		if(c == ' ')
			return PAGELEN;
		if(c == '\n')
			return 1;
	} 
	return 0;
} 










