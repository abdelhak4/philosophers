

#include "philo_bonus.h"

int main()
{
	pid_t state;
	int i = -1, re[3];
	while (++i < 3)
	{
		if ((re[i] = fork()) == -1)
			printf("fork(): failed to creat child\n");
		if (re[i] == 0)
		{
			 //child process and calling of routing function
			printf("here is the child %d\n", i);
			sleep(1);
			return 0;
//			break;
		}
	}
//	if (re[i] == 0)
//	{
//		printf("here we go again %d\n", i);
//	}
	printf("this is parrt\n");
	waitpid(-1, &state, 0);
	return (2);
}