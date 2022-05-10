#include <stdio.h>
#include <sys/time.h>


int main()
{
	struct  timeval ss;
	struct  timeval s;
	gettimeofday(&s, NULL);
	sleep(1);
	gettimeofday(&ss, NULL);
	long long t = (ss.tv_usec /1000) + (ss.tv_sec * 1000);
	printf("%lld",t - (s.tv_usec /1000) + (s.tv_sec * 1000));
}