/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 20 22/04/17 15:42:17 by ael-mous          #+#    #+#             */
/*   Updated: 2022/04/17 15:42:19 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing(t_data **vars, char **av)
{
	(*vars)->n_of_philo = ft_atoi(av[1]);
	(*vars)->time_to_die = ft_atoi(av[2]);
	(*vars)->time_to_eat = ft_atoi(av[3]);
	(*vars)->time_to_sleep = ft_atoi(av[4]);
	//(*vars)->n_time_to_each_ph_to_eat = ft_atoi(av[5]);
}
void	*rout(void	*arg)
{
	int 	add;
	t_data	*var;

	var = (t_data*)arg;
	if (var->state == 0)
	{
		printing_msg(var, 0, var->ph[var->i]);
		printing_msg(var, 3,var->ph[var->i]);
	}
	return NULL;
}
/*
 *     here I created threads
 */
void	philos(t_data *vars, char **av)
{
	int i;
	int j;
	pthread_t id[vars->n_of_philo];
	pthread_mutex_t	fork_lock[vars->n_of_philo];

	i = 0;
	j = -1;
	vars->ph = malloc(vars->n_of_philo * sizeof(int));
	gettimeofday(&vars->time, NULL);
	/*
	 ? init time var
	 */
	vars->Start_t = m_time(vars);
	vars->End_t = m_time(vars);
	pthread_mutex_init(&vars->lock, NULL);
	while (++j < vars->n_of_philo)
		pthread_mutex_init(&fork_lock[j], NULL);
	vars->state = 0;
	vars->fork_lock = fork_lock;
	while (i < vars->n_of_philo)
	{
		vars->ph[i] = i + 1;
		vars->i = i;
		if (pthread_create(id + i, NULL, &rout, vars) != 0)
		{
			printf("err in creating thread");
			return ;
		}
		usleep(100);
		i++;
	}
}
int	main(int ac, char **av)
{
	t_data *vars;

	if (ac == 5) {
		vars = malloc(sizeof(t_data));
		if (!vars)
		{
			return 1;
		}
		parsing(&vars, av);
		philos(vars, av);
	}
	else
		printf("err arg should contains 4 args\n");
	return (0);
}





