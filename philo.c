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
/*
 *
 		! "Note" TODO : handle max int and min int in ft_atoi.c
 *
 */

void	parsing(t_data **vars, char **av)
{
	(*vars)->n_of_philo = ft_atoi(av[1]);
	(*vars)->time_to_die = ft_atoi(av[2]);
	(*vars)->time_to_eat = ft_atoi(av[3]);
	(*vars)->time_to_sleep = ft_atoi(av[4]);
	//(*vars)->n_time_to_each_ph_to_eat = ft_atoi(av[5]);
}

void	is_eating(t_data *var, int ph)
{
	pthread_mutex_lock(&var->fork_lock[ph]);
	print_msg(var, ph, "has taken a fork");
	pthread_mutex_lock(&var->fork_lock[ph + 1]);
	print_msg(var, ph, "has taken a fork");
	pthread_mutex_lock(&var->lock);
	print_msg(var, ph, "is eating");
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

void	check_for_die(t_data *var)
{

}

void	*rout(void	*arg)
{
	t_data	*var;

	var = (t_data*)arg;
	while (check_for_die(var))
	{
		var->Start_t = m_time(var);
		is_eating(var, var->ph[var->i]);
		is_sleeping(var, var->ph[var->i]);
		is_thinking(var, var->ph[var->i]);
		var->End_t = m_time(var);
	}
	return NULL;
}
/*
 *     here I created threads
 */
void	philo(t_data *vars, char **av)
{
	int	i;
	int	j;
	pthread_t id[vars->n_of_philo];
	pthread_mutex_t	fork_lock[vars->n_of_philo];

	i = 0;
	j = -1;
	vars->ph = malloc(vars->n_of_philo * sizeof(int));
	/*
	 ? init time variables
	 */
	pthread_mutex_init(&vars->lock, NULL);
	while (++j < vars->n_of_philo) {
		pthread_mutex_init(&fork_lock[j], NULL);
	}
	vars->state = 0;
	vars->fork_lock = fork_lock;
	vars->End_t = m_time(vars);
	while (i < vars->n_of_philo)
	{
		vars->ph[i] = i + 1;
		vars->i = i;
		if (pthread_create(id + i, NULL, &rout, vars) != 0)
		{
			printf("err in creating thread");
			return ;
		}
		usleep(1000);
		i++;
	}
	j = 0;
	//  TODO : check if philo not die !!
	if (vars->die == -1)
		return;
	while (j < vars->n_of_philo)
	{
		if (pthread_join(*(id + j), NULL) != 0)
		{
			printf("err in creating thread");
			return ;
		}
		j++;
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
		philo(vars, av);
	}
	else
		printf("err arg should contains 4 args\n");
	return (0);
}





