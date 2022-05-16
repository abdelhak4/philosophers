#include "philo.h"

void	down_forks(t_data *var, int f_right, int f_left)
{
	pthread_mutex_unlock(&var->fork_lock[f_right]);
	pthread_mutex_unlock(&var->fork_lock[f_left]);
}

unsigned long m_time(t_data *vars)
{
	gettimeofday(&vars->time, NULL);
	return ((vars->time.tv_sec * 1000) + (vars->time.tv_usec/1000));
}

void	print_msg(t_data *var, int ph, char *str)
{
	var->t = m_time(var) - var->Start_t;
	printf("%ld ms ", var->t);
	printf("%d %s\n", ph, str);
}
