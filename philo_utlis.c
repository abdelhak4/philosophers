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

int	is_eating(t_data *var, int ph)
{
	if (var->t > var->time_to_die) {
		var->die = -1;
		return 0;
	}
	printf("%ld ms %d is eating\n", var->t, ph);
	var->state = 1;
	gettimeofday(&var->time, NULL);
	var->End_t = m_time(var);
	usleep(var->time_to_eat * 1000);
	return 1;
}

/*
   ! state '0' for thinking
   ! state '1' for fork
   ! state '2' for sleeping
   ! state '3' for eating or died
 */
void	printing_msg(t_data *var, int state, int ph)
{
	pthread_mutex_lock(&var->lock);
	var->t = var->End_t - var->Start_t;
	if (state == 0)
		printf("%ld ms %d is thinking\n", var->t, ph);
	else if (state == 1)
	{
		pthread_mutex_lock(&var->fork_lock[ph]);
		pthread_mutex_lock(&var->fork_lock[ph + 1]);
		printf("%ld ms %d has taken a fork\n", var->t, ph);
		printf("%ld ms %d has taken a fork\n", var->t, ph);
	}
	else if (state == 2)
	{
		printf("%ld ms %d is sleeping\n", var->t, ph);
		usleep(var->time_to_sleep * 1000);
	}
	else if (state == 3) {
		if (is_eating(var, ph) == 0) {
			printf("%ld ms %d died\n", var->t,ph);
			var->die = -1;
			return;
		}
	}
	pthread_mutex_unlock(&var->lock);
}