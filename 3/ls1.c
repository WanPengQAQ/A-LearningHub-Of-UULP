#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>

void do_ls(char []);
int main(int ac, char* av[])
{
	if(ac == 1)
		do_ls(".");
	else{
		int i;
		for(i = 0; i < ac; i++)
			do_ls(av[i]);
	}	
}

void do_ls(char dirname[])
{
	DIR *dir_ptr;   // name of dir
	struct dirent* direntp;
	if((dir_ptr = opendir(dirname)) == NULL){
		fprintf(stderr, "ls1 cannot open %s \n",dirname);
	} else {
		while((direntp = readdir(dir_ptr)) != NULL){
			printf("%s\n",direntp->d_name);
		}
		closedir(dir_ptr);
	}
}
