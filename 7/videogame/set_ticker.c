#include<stdio.h>
#include<signal.h>
#include<sys/time.h>

void set_ticker(int time) //set interval timer, ms
{
	struct itimerval newtimer;
	int seconds = time/1000;
	int usec = (time%1000)*1000;
	
	newtimer.it_value.tv_sec = seconds;
	newtimer.it_value.tv_usec = usec;

	newtimer.it_interval.tv_sec = seconds;
	newtimer.it_interval.tv_usec = usec;

	setitimer(ITIMER_REAL, &newtimer, NULL);
}

