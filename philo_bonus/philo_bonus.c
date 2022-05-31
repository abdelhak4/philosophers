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
void *rout(void *arg)
{
	int i;
	t_data *this;

	this = (t_data*)arg;
	i = 0;
	while (1)
	{
		if (i == this->n_of_ph)
			i = 0;
		sem_wait(this->var);
		if (m_time() - this->start_t - this->last_eat >=
			this->time_to_die)
		{
			sem_wait(this->lock);
			this->is_died = 1;
			printf("%s%ld ms {%lu} \"%s\"\n", RED, (m_time() - this->start_t), this->ph + 1,"is died");
			kill(0, 2);
			break;
		}
		sem_post(this->var);
		usleep(100);
		i++;
	}
	return NULL;
}
int	routine(t_data *data, int *pid)
{
	pthread_t	id;

	if (pthread_create(&id, NULL, &rout, (void *)data) != 0)
	{
		printf("err in creating thread");
		return 0;
	}
	while (1)
	{
		sem_wait(data->lock);
		if (data->is_died == 1)
			break;
		sem_post(data->lock);
		is_eating(data, data->ph);
		is_thinking(data, data->ph);
		is_sleeping(data, data->ph);
	}
	return 1;
}


int	create_philo(t_data *data)
{
	pid_t	state;
	pid_t	*re;
	char	*ptr;
	char	*sem;
	int		i;

	i = -1;
	ptr = "semaphore1";
	sem = "lock";
	re = malloc(sizeof(pid_t) * data->n_of_ph);
	if (!re)
		return (4);
	data->start_t = m_time();
	sem_unlink(ptr);
	sem_unlink(sem);
	sem_unlink("vars");
	data->sem = sem_open(ptr, O_CREAT, 0644, data->n_of_ph);
	data->var = sem_open("vars", O_CREAT, 0644, 1);
	if (data->sem == SEM_FAILED)
		return -1;
	data->lock = sem_open(sem, O_CREAT, 0644, 1);
	while (++i < data->n_of_ph)
	{
		if ((re[i] = fork()) == -1) {
			printf("fork(): failed to creat child\n");
		}
		if (re[i] == 0)
		{
			sem_wait(data->lock);
			data->ph = i;
			sem_post(data->lock);
			routine(data, re);
			sem_unlink(ptr);
			sem_unlink(sem);
			return 0;
		}
		usleep(100);
	}
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





