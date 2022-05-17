#include "philo.h"

void	parsing(t_data **vars, char **av, int ac)
{
	(*vars)->n_of_philo = ft_atoi(av[1]);
	(*vars)->time_to_die = ft_atoi(av[2]);
	(*vars)->time_to_eat = ft_atoi(av[3]);
	(*vars)->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*vars)->n_time_to_each_ph_to_eat = ft_atoi(av[5]);
	else
		(*vars)->n_time_to_each_ph_to_eat = -1;
}

void	down_forks(t_data *var, int f_right, int f_left)
{
	pthread_mutex_unlock(&var->fork_lock[f_right]);
	pthread_mutex_unlock(&var->fork_lock[f_left]);
}

time_t	m_time(t_data *vars)
{
	gettimeofday(&vars->time, NULL);
	return ((vars->time.tv_sec * 1000) + (vars->time.tv_usec/1000));
}

void	print_msg(t_data *var, int ph, char *str)
{
	var->philo->t = m_time(var) - var->philo->Start_t;
	printf("%ld ms ", var->philo->t);
	printf("%d %s\n", ph, str);
}
