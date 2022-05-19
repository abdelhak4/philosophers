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

void	down_forks(t_data **var, int ph)
{
	pthread_mutex_unlock(&(*var)->fork_lock[(*var)->s_ph[ph].l_fork]);
	pthread_mutex_unlock(&(*var)->fork_lock[(*var)->s_ph[ph].r_fork]);
}

time_t	m_time()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec/1000));
}

void	print_msg(t_data *var, int ph, char *str)
{
	var->s_ph[ph].t = m_time() - var->Start_t;
	printf("%ld ms ", var->s_ph->t);
	printf("%d %s\n", ph + 1, str);
}
