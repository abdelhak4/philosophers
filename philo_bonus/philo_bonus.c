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

#include "philo_bonus.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

void	parsing(t_data **vars, char **av, int ac)
{
	int i;
	int j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isalpha(av[i][j]))
			{
				printf("hmm\n");
				return;
			}
			j++;
		}
		i++;
	}
	(*vars)->n_of_ph = ft_atoi(av[1]);
	(*vars)->time_to_die = ft_atoi(av[2]);
	(*vars)->time_to_eat = ft_atoi(av[3]);
	(*vars)->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*vars)->n_time_to_each_ph_to_eat = ft_atoi(av[5]);
	else
		(*vars)->n_time_to_each_ph_to_eat = -1;
}

  //@ todo check if not someone is died ??//
  int	routine(t_data *data)
  {
	int k = 15;
	while (k) {
		is_eating(data, data->ph);
		is_thinking(data, data->ph);
		is_sleeping(data, data->ph);
		k--;
	}
	return 0;
}


int	create_philo(t_data *data)
{
	pid_t	state;
	pid_t	*re;
	int		i;
	int 	j;

	i = -1;
	j = 0;
	re = malloc(sizeof(pid_t) * data->n_of_ph);
	if (!re)
		return (4);
	data->start_t = m_time();
	data->sem = sem_open("semaphore", O_CREAT, 0644, data->n_of_ph);
	data->lock = sem_open("lock", O_CREAT, 0644, 1);
	while (++i < data->n_of_ph)
	{
		if ((re[i] = fork()) == -1)
			printf("fork(): failed to creat child\n");
		if (re[i] == 0)
		{
			routine(data);
			return 0;
		}
		//usleep(100);
	}
//	if (re[i] == 0)// I am in the child process
//	{
//		sem_
//		data->ph = i;
//		routine(data);
//	}
	waitpid(-1, &state, 0);
	return (2);
}

int	main(int ac, char **av)
{
	t_data *vars;

	if (ac == 5 || ac == 6) {
		vars = malloc(sizeof(t_data));
		if (!vars)
		{
			return (1);
		}
		parsing(&vars, av, ac);
		create_philo(vars);
	}
	else
		printf("err arg should contains 5 args at least\n");
	return (0);
}





