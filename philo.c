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
	(*vars)->n_of_philo = atoi(av[1]);
	(*vars)->time_to_die = atoi(av[2]);
	(*vars)->time_to_eat = atoi(av[3]);
	(*vars)->time_to_sleep = atoi(av[4]);
}

void	*rout(void	*arg)
{
	t_data *var;

	var = (*t_data)arg;

	return NULL;
}
void	philos(t_data *vars)
{
	int i;
	pthread_t id[vars->n_of_philo];

	i = 0;
	if(!gettimeofday(&vars->time, NULL))
	{
		printf("err in gettimeofday\n");
		return ;
	}
	vars->sec = (vars->time.tv_sec * 1000) + (vars->time.tv_usec/1000);

	while (i < vars->n_of_philo)
	{
		if (pthread_create(id + i, NULL, &rout, vars) == 0)
		{
			printf("err in creating thread");
			return;
		}
		vars = malloc(sizeof(t_data));
		if (!vars)
		{
			return 1;
		}
		parsing(&vars, av);
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
		philos(vars);
	}
	else
		printf("err arg should contains 4 args\n");
	return (0);
}





