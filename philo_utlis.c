#include "philo.h"
/*
 ?  my-usleep
 ?	parsing - down_forks
 ?	m_time print_msg
 */

void	my_usleep(t_data *var, time_t t)
{
	pthread_mutex_lock(&var->lock);
	time_t	t0 = m_time();
	while (m_time() - t0 < t)
		usleep(51);
	pthread_mutex_unlock(&var->lock);
}

void	print_msg(t_data *var, int ph, char *str, char *clr)
{
	pthread_mutex_lock(&var->write);
	printf("%s%ld ms {%d} \"%s\"\n",clr , (m_time() - var->Start_t), ph + 1, str);
	pthread_mutex_unlock(&var->write);
}

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

time_t	m_time()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec/1000));
}
