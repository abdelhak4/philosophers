#include "philo.h"

t_ph 	vars_init(t_data *vars, int i)
{
	vars->s_ph[i].ph = i;
	vars->s_ph[i].r_fork = i+1 % vars->n_of_philo;
	vars->s_ph[i].l_fork = i;
	vars->s_ph[i].eat = 0;
	vars->s_ph[i].t = 0;
	vars->s_ph[i].eat_times = 0;
	return vars->s_ph[i];
}
void	is_eating(t_data *var, int ph)
{
	pthread_mutex_lock(&var->fork_lock[var->s_ph[ph].l_fork]);
	print_msg(var, ph, "has taken a fork");
	pthread_mutex_lock(&var->fork_lock[var->s_ph[ph].r_fork]);
	print_msg(var, ph, "has taken a fork");
	pthread_mutex_lock(&var->write);
	print_msg(var, ph, "is eating");
	var->s_ph->eat_times++;
	usleep(var->time_to_eat * 1000);
	pthread_mutex_unlock(&var->write);
	down_forks(&var, ph);
}

void	is_sleeping(t_data *var, int ph)
{
	pthread_mutex_lock(&var->write);
	print_msg(var, ph, "is sleeping");
	pthread_mutex_unlock(&var->write);
	usleep(var->time_to_sleep * 1000);
}

void	is_thinking(t_data *var, int ph)
{
	print_msg(var, ph, "is thinking");
	usleep(var->time_to_sleep * 1000);
}

int	check_for_die(t_data *var)
{
	if (var->s_ph->eat_times >= var->n_time_to_each_ph_to_eat)
		return 0;
	if (var->s_ph->t > var->time_to_die)
		return 0;
	return 1;
}
