#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>

#define BUFSIZE 100

ino_t get_inode(char*);
void printpathto(ino_t);
void inum_to_name(ino_t, char*, int);

int main(int ac, char *av[])
{
	printpathto(get_inode("."));
	putchar('\n');
	
	return 0;
}

void printpathto(ino_t this_inode)
{
	ino_t my_inode;
	char its_name[BUFSIZE];
	
	if(get_inode("..") != this_inode) { //if not root
		chdir("..");					//up dir
		inum_to_name(this_inode, its_name, BUFSIZE);	//get son dir name
		my_inode = get_inode(".");
		printpathto(my_inode);
		printf("/%s", its_name);
	}
}
ino_t get_inode(char *filename)
{
	struct stat info;
	if(stat(filename, &info) == 0){
		return info.st_ino;
	} else {
		fprintf(stderr, "Cannot get inode\n");
		exit(1);
	}
}
void inum_to_name(ino_t inode_to_find, char *namebuf, int buflen)
{
	DIR* dir_p;
	struct dirent* dirent_p;
	
	if((dir_p=opendir(".")) != NULL){
		while((dirent_p=readdir(dir_p))!=NULL){
			if(dirent_p->d_ino == inode_to_find)
				break;	
		}	
		strcpy(namebuf, dirent_p->d_name);
		closedir(dir_p);
	} else {
		namebuf = NULL;
	}

}











