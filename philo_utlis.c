#include "philo.h"

unsigned long m_time(t_data *vars)
{
	return ((vars->time.tv_sec * 1000) + (vars->time.tv_usec/1000));
}

int	is_eating(t_data *var, int ph)
{
	gettimeofday(&var->time, NULL);
	var->End_t = m_time(var);
	var->t = var->End_t - var->Start_t;
	if (var->t > var->time_to_die)
		return 0;
	printf("%ld ms %d is eating\n", var->t, ph);
	return 1;
}

/*
   ! state 0 for thinking
   ! state 1 for fork
   ! state 2 for sleeping
   ! state 3 for eating or died
 */
void	printing_msg(t_data *var, int state, int ph)
{
	pthread_mutex_lock(&var->lock);
	if (state == 0)
		printf("%ld ms %d is thinking\n", var->t, ph);
	else if (state == 1)
		printf("%ld ms %d has taken a fork\n", var->t, ph);
	else if (state == 2)
		printf("%ld ms %d is sleeping\n", var->t, ph);
	else if (state == 3) {
		if (is_eating(var, ph) == 0) {
			printf("%ld ms %d died\n", var->t,ph);
			var->die = -1;
			return;
		}
	}
	pthread_mutex_unlock(&var->lock);
}