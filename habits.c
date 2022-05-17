#include "philo.h"

void	vars_init(t_data *vars, int i)
{
	vars->philo[i].ph = i + 1;
	vars->philo[i].i = i;
	vars->philo[i].r_fork = (i - 1) % vars->n_of_philo;
	vars->philo[i].eat = 0;
	vars->philo[i].t = 0;
	vars->philo[i].eat_times = 0;
}
void	is_eating(t_data *var, int ph)
{
	pthread_mutex_lock(&var->fork_lock[ph]);
	print_msg(var, ph, "has taken a fork");
	pthread_mutex_lock(&var->fork_lock[var->philo->r_fork]);
	print_msg(var, ph, "has taken a fork");
	pthread_mutex_lock(&var->lock);
	print_msg(var, ph, "is eating");
	var->philo->eat_times++;
	usleep(var->time_to_eat * 1000);
	pthread_mutex_unlock(&var->lock);
	down_forks(var, ph, ph +1);
}

void	is_sleeping(t_data *var, int ph)
{
	print_msg(var, ph, "is sleeping");
	usleep(var->time_to_sleep * 1000);
}

void	is_thinking(t_data *var, int ph)
{
	print_msg(var, ph, "is thinking");
	usleep(var->time_to_sleep * 1000);
}

int	check_for_die(t_data *var)
{
	if (var->philo->eat_times >= var->n_time_to_each_ph_to_eat)
		return 0;
	if (var->philo->t > var->time_to_die)
		return 0;
	return 1;
}
