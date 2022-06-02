/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:37:17 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/01 15:37:27 by ael-mous         ###   ########.fr       */
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
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isalpha(av[i][j]))
			{
				printf("Error\n");
				return ;
			}
			j++;
		}
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

int	all_eat(t_data *var)
{
	if (var->eat_times > var->n_time_to_each_ph_to_eat)
		return (1);
	return (0);
}

void	*rout_for_check_died(void *arg)
{
	int		i;
	t_data	*this;

	this = (t_data *)arg;
	i = 0;
	while (1)
	{
		if (i == this->n_of_ph)
			i = 0;
		sem_wait(this->var);
		if (m_time() - this->start_t - this->last_eat
			>= this->time_to_die)
		{
			sem_wait(this->lock);
			this->is_died = 1;
			printf("%s%ld ms {%lu} \"%s\"\n", RED, (m_time() - this->start_t),
				this->ph + 1, "is died");
			kill(0, 2);
			break ;
		}
		sem_post(this->var);
		usleep(100);
		i++;
	}
	return (NULL);
}

int	routine(t_data *data)
{
	pthread_t	id;

	if (pthread_create(&id, NULL, &rout_for_check_died, (void *)data) != 0)
	{
		printf("err in creating thread");
		return (0);
	}
	while (1)
	{
		sem_wait(data->lock);
		sem_post(data->lock);
		is_eating(data, data->ph);
		if (all_eat(data))
		{
			kill(0, SIGKILL);
			exit(EXIT_SUCCESS);
		}
		is_sleeping(data, data->ph);
	}
	return (1);
}
void init(t_data *data, pid_t **re)
{
	*re = malloc(sizeof(pid_t) * data->n_of_ph);
	if (!(*re))
		exit(EXIT_FAILURE);
	data->start_t = m_time();
	sem_unlink("open");
	sem_unlink("sem");
	sem_unlink("vars");
	data->sem = sem_open("open", O_CREAT | O_EXCL, 0644, data->n_of_ph);
	data->var = sem_open("vars", O_CREAT | O_EXCL, 0644, 1);
	data->lock = sem_open("sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->sem == SEM_FAILED || data->var == SEM_FAILED
		|| data->lock == SEM_FAILED)
		exit(EXIT_FAILURE);
}

int	create_philo(t_data *data)
{
	pid_t	state;
	pid_t	*re;
	int		i;

	i = -1;
	init(data, &re);
	while (++i < data->n_of_ph)
	{
		re[i] = fork();
		if (re[i] == -1)
		{
			printf("fork(): failed to creat child\n");
			exit(EXIT_FAILURE);
		}
		if (re[i] == 0)
		{
			data->ph = i;
			routine(data);
			return (4);
		}
		usleep(100);
	}
	waitpid(-1, &state, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*vars;

	if (ac == 5 || ac == 6)
	{
		vars = malloc(sizeof(t_data));
		if (!vars)
		{
			return (1);
		}
		parsing(&vars, av, ac);
		if (vars->n_time_to_each_ph_to_eat == 0)
			return (3);
		vars->eat_times = 0;
		create_philo(vars);
		sem_unlink("open");
		sem_unlink("vars");
		sem_unlink("sem");
	}
	else
		printf("err arg should contains 5 args at least\n");
	return (0);
}
