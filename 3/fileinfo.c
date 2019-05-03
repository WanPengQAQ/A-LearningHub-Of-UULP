#include<stdio.h>
#include<sys/stat.h>
#include<time.h>

void show_stat_info(char [], struct stat *buf);
int main(int ac, char *av[])
{
	struct stat info;
	if(ac == 2){
		if(stat(av[1], &info) == 0 ){
			show_stat_info(av[1], &info);	
		} else {
			printf("cannot open %s\n",av[1]); 
		}
	} else {
		printf("leak arguments\n");
	}
}

void show_stat_info(char dirname[], struct stat *buf)
{
	printf("   mode: %o\n", buf->st_mode);
	printf("  links: %d\n", buf->st_nlink);
	printf("   user: %d\n", buf->st_uid);
	printf("  group: %d\n", buf->st_gid);
	printf("   size: %d\n", buf->st_size);
	printf("modtime: %s\n", ctime(&(buf->st_mtime)));
	printf("   name: %s\n", dirname);	
}
