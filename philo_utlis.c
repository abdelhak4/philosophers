#include "philo.h"
/*
 ?  my-usleep
 ?	parsing - down_forks
 ?	m_time print_msg
 */

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

t_ph 	vars_init(t_data *vars, int i)
{
	pthread_mutex_lock(&vars->mut);
	vars->i = i;
	vars->s_ph[i].ph = i;
	vars->s_ph[i].last_eat = 0;
	vars->s_ph[i].r_fork = (i + 1) % vars->n_of_philo;
	vars->s_ph[i].l_fork = i;
	vars->s_ph[i].eat = 0;
	vars->s_ph[i].eat_times = 0;
	vars->s_ph[i].last_eat = 0;
	pthread_mutex_unlock(&vars->mut);
	return vars->s_ph[i];
}

void	my_usleep(t_data *var, time_t t)
{
	time_t	t0 = m_time();
	while (m_time() - t0 < t)
		usleep(51);
}

void	print_msg(t_data *var, int ph, char *str, char *clr)
{
	pthread_mutex_lock(&var->write);
	printf("%s%ld ms {%d} \"%s\"\n",clr , (m_time() - var->start_t),
		   ph + 1, str);
	pthread_mutex_unlock(&var->write);
}

void	parsing(t_data **vars, char **av, int ac)
{
	int	i;
	int j;

	i = 1;
	while (i < ac -1)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isalpha(av[i][j]))
			{
				printf("hmm\n");
				return;
			}
			j++;
		}
		i++;
	}
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
