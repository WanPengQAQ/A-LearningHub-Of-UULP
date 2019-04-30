#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>


#define NRECS 16
#define NULLUT ((struct utmp*)NULL)  //new
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NRECS * UTSIZE]; //buff
static int num_recs;		     //total number in buff	
static int cur_rec;       	     //next index
static int fd_utmp=-1;		     //read from this fd

int utmp_open(const char* filename)	//return fd of utmp, if faliure return -1
{	
	fd_utmp = open(filename, O_RDONLY);
	cur_rec =0;
	num_recs = 0;
	return fd_utmp;
}

int utmp_reload()		//return how many utmp struct we have got, failure return 0
{
	int amt_read;
	amt_read = read(fd_utmp, utmpbuf, NRECS*UTSIZE);
	if(amt_read == -1)	//read utmp file faliure
		return 0;
	num_recs = amt_read/UTSIZE;
	cur_rec = 0;
	return num_recs;
}

struct utmp* utmp_next() 
{
	if(fd_utmp == -1)
		return NULLUT;
	if(cur_rec == num_recs && utmp_reload() == 0) //buff is full and cannot reload from fd_utmp
		return NULLUT;
	struct utmp *recp;
	recp = (struct utmp*)(&utmpbuf[cur_rec * UTSIZE]);
	cur_rec++;
	return recp;
}
void utmp_close()
{
	if(fd_utmp != -1){
		close(fd_utmp);
	}
}
