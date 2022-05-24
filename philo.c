/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 20 22/04/17 15:42:17 by ael-mous          #+#    #+#             */
/*   Updated: 2022/05/19 20:27:59 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
 *
 		! "Note" TODO : handle max int and min int in ft_atoi.c
 *
 */

void	*rout(void	*arg)
{
	int 	ph;
	t_data	*var;

	var = (t_data*)arg;
	ph = var->s_ph[var->i].ph;
	while (1)
	{
		pthread_mutex_lock(&var->lock);
		if (var->is_died == 1)
			break;
		pthread_mutex_unlock(&var->lock);
		is_eating(var, ph);
		is_sleeping(var, ph);
		is_thinking(var, ph);
	}
	return NULL;
}

int	philo(t_data *vars, char **av)
{
	int				i;
	int				j;
	pthread_t 		*id;

	i = 0;
	j = 0;
	if (!(id = malloc(sizeof(pthread_t) * vars->n_of_philo)))
		return 0;
	if (!(vars->s_ph = malloc(sizeof(t_ph) * vars->n_of_philo)))
		return 0;
	(*vars).start_t = m_time();
	(*vars).die = 0;
	(*vars).is_died = 0;
	while (i < vars->n_of_philo)
	{
		vars->s_ph[i] = vars_init(vars , i);
		vars->i = i;
		if (pthread_create(id + i, NULL, &rout, (void *)vars) != 0)
		{
			printf("err in creating thread");
			return 0;
		}
		usleep (100);
		i++;
	}
	if (check_for_die(vars))
		return 0;
	return 1;
}

void	init_mutex(t_data **vars)
{
	int				j;

	(*vars)->fork = malloc(sizeof(pthread_mutex_t) * (*vars)->n_of_philo);
	j = -1;
	pthread_mutex_init(&(*vars)->lock, NULL);
	pthread_mutex_init(&(*vars)->write, NULL);
	while (++j < (*vars)->n_of_philo)
		pthread_mutex_init(&(*vars)->fork[j], NULL);
}

int	main(int ac, char **av)
{
	t_data *vars;

	if (ac == 5) {
		vars = malloc(sizeof(t_data));
		if (!vars)
		{
			return (1);
		}
		parsing(&vars, av, ac);
		init_mutex(&vars);
		if (philo(vars, av))
			return 1;
	}
	else
		printf("err arg should contains 4 args at least\n");
	return (0);
}





