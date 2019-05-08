#include<stdio.h>
#include<signal.h>

void wakeup(int x)
{
	printf("Alarm received from kernel\n");
}

int main()
{
	printf("about sleep for 4 seconds\n");
	signal(SIGALRM, wakeup);
	alarm(4);
	pause();
	printf("gogogo\n");
	return 0;
}
