/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:51:31 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/01 10:51:39 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
 		! todo : destroy mutexes!!
 *
 */

int	check_arg(char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isalpha(av[i][j]) || av[i][j] == '-')
			{
				printf("Error\n");
				return (1);
			}
			j++;
		}
	}
	return (0);
}

void	*rout(void	*arg)
{
	int		ph;
	t_data	*var;

	var = (t_data *)arg;
	pthread_mutex_lock(&var->mut);
	ph = var->s_ph[var->i].ph;
	pthread_mutex_unlock(&var->mut);
	while (1)
	{
		is_eating(var, ph);
		pthread_mutex_lock(&var->mut);
		if (var->is_died == 1)
			break ;
		pthread_mutex_unlock(&var->mut);
		is_sleeping(var, ph);
		print_msg(var, ph, "is thinking", CYAN);
	}
	return (NULL);
}

int	philo(t_data *vars)
{
	int			i;
	pthread_t	*id;

	i = -1;
	id = malloc(sizeof(pthread_t) * vars->n_of_philo);
	if (!id)
		return (1);
	vars->s_ph = malloc(sizeof(t_ph) * vars->n_of_philo);
	if (!vars->s_ph)
		return (2);
	(*vars).start_t = m_time();
	while (++i < vars->n_of_philo)
	{
		vars->s_ph[i] = vars_init(vars, i);
		if (pthread_create(id + i, NULL, &rout, (void *)vars) != 0)
		{
			printf("err in creating thread");
			return (3);
		}
		usleep (100);
	}
	check_for_die(vars);
	destroy_mutex(vars);
	return (0);
}

int	init_mutex(t_data **vars)
{
	int	j;

	(*vars)->fork = malloc(sizeof(pthread_mutex_t) * (*vars)->n_of_philo);
	if (!(*vars)->fork)
		return (1);
	j = -1;
	if (pthread_mutex_init(&(*vars)->lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*vars)->mut, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*vars)->sleep, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*vars)->write, NULL) != 0)
		return (1);
	while (++j < (*vars)->n_of_philo)
		if (pthread_mutex_init(&(*vars)->fork[j], NULL) != 0)
			return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*vars;

	if (ac == 5 || ac == 6)
	{
		vars = malloc(sizeof(t_data));
		if (!vars)
			return (1);
		if (parsing(&vars, av, ac) != 0)
			return (2);
		if (vars->n_time_to_each_ph_to_eat == 0)
			return (3);
		if (init_mutex(&vars) != 0)
			return (4);
		(*vars).die = 0;
		(*vars).is_died = 0;
		if (philo(vars) != 0)
			return (5);
	}
	else
		printf("err arg should contains 4 args at least\n");
	return (0);
}
