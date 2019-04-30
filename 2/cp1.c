#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFERSIZE 4096
#define COPEMODE   0644

int main(int ac, char *av[])
{
	if(ac == 1 || ac == 2){
		printf("missing file operand\n");
		exit(1); 
	} else if (ac == 3){
		int in_fp, out_fp, n_chars;
		char buf[BUFFERSIZE];
		if( (in_fp=open(av[1],O_RDONLY)) == -1 ){ //open source file for reading
			printf("Cannot open %s\n",av[1]);
			exit(1);
		}		
		if(out_fp = creat(av[2],COPEMODE) == -1){ //open copyfile for writing
			printf("Cannot creat %s\n",av[2]);
			exit(1);
		}
		while( (n_chars=read(in_fp,buf,BUFFERSIZE))>0 ){ //copy source file to copyfile
			if(write(out_fp,buf,n_chars) != n_chars){
				printf("write error in %s\n",av[2]);
				exit(1);
			}	
		}
		if(n_chars == -1){
			printf("read error in %s\n",av[1]);
			exit(1);
		}
		if(close(in_fp) == -1 || close(out_fp) == -1){
			printf("close error\n");
			exit(1);
		}
	} else {
		fprintf(stderr, "arg too much\n");
		exit(1);
	}

	return 0;
}
