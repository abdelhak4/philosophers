#include "philo.h"
/*
 ?  contains vars_init
 ?	is_eating and is_sleeping , is_thinking
 ?	and check_for_die
 */
t_ph 	vars_init(t_data *vars, int i)
{
	vars->s_ph[i].ph = i;
	vars->s_ph[i].r_fork = (i + 1) % vars->n_of_philo;
	vars->s_ph[i].l_fork = i;
	vars->s_ph[i].eat = 0;
	vars->s_ph[i].t = 0;
	vars->s_ph[i].eat_times = 0;
	vars->s_ph[i].last_eat = 0;
	return vars->s_ph[i];
}

void	is_eating(t_data *var, int ph)
{
	pthread_mutex_lock(&var->fork[var->s_ph[ph].l_fork]);
	print_msg(var, ph, "has taken  the left fork");
	pthread_mutex_lock(&var->fork[var->s_ph[ph].r_fork]);
	print_msg(var, ph, "has taken the right  fork");
	print_msg(var, ph, "is eating");
	//var->s_ph[ph].eat_times++;
	var->s_ph[ph].last_eat = m_time() - var->Start_t;
	my_usleep(var, var->time_to_eat);
	pthread_mutex_unlock(&var->fork[var->s_ph[ph].l_fork]);
	pthread_mutex_unlock(&var->fork[var->s_ph[ph].r_fork]);
}

void	is_sleeping(t_data *var, int ph)
{
	pthread_mutex_lock(&var->write);
	print_msg(var, ph, "is sleeping");
	my_usleep(var, var->time_to_sleep);
	pthread_mutex_unlock(&var->write);
}

void	is_thinking(t_data *var, int ph)
{
	pthread_mutex_lock(&var->write);
	print_msg(var, ph, "is thinking");
	pthread_mutex_unlock(&var->write);
}

int	check_for_die(t_data *var, int i)
{
	time_t	result;

	result = var->s_ph[i].last_eat + var->time_to_die;
	if (var->s_ph[i].eat_times >= var->n_time_to_each_ph_to_eat)
		return 0;
	if (result < (m_time() - var->Start_t))
		return 0;
	return 1;
}
