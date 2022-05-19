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

void	*rout(void	*arg)
{
	int 	i;
	t_data	*var;

	var = (t_data*)arg;
	i = var->s_ph[var->i].ph;
	if (i % 2 != 0)
		usleep(100);
	while (1)
	{
		is_eating(var, i);
		is_sleeping(var, i);
//		is_thinking(var, var->philo->ph);
	}
	return NULL;
}

void	philo(t_data *vars, char **av)
{
	int				i;
	int				j;
	pthread_t		id[vars->n_of_philo];

	i = 0;
	if (!(vars->s_ph = malloc(sizeof(t_ph) * vars->n_of_philo)))
		return;
	(*vars).Start_t = m_time(vars);
	while (i < vars->n_of_philo)
	{
		vars->s_ph[i] = vars_init(vars , i);
		vars->i = i;
		if (pthread_create(id + i, NULL, &rout, (void *)vars) != 0)
		{
			printf("err in creating thread");
			return ;
		}
		usleep(10);
		i++;
	}
	j = 0;
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

void	init_mutex(t_data **vars)
{
	int				j;
	pthread_mutex_t	fork_lock[(*vars)->n_of_philo];

	j = -1;
	pthread_mutex_init(&(*vars)->lock, NULL);
	pthread_mutex_init(&(*vars)->write, NULL);
	while (++j < (*vars)->n_of_philo)
		pthread_mutex_init(&fork_lock[j], NULL);
	(*vars)->fork_lock = fork_lock;

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
		philo(vars, av);
	}
	else
		printf("err arg should contains 4 args at least\n");
	return (0);
}





