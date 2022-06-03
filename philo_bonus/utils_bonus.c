/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:45:50 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/03 10:45:52 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	all_eat(t_data *var)
{
	if (var->eat_times > var->n_time_to_each_ph_to_eat)
		return (1);
	return (0);
}

void	close_sem(t_data *this)
{
	sem_close(this->var);
	sem_close(this->lock);
	sem_close(this->sem);
}

void	init(t_data *data, pid_t **re)
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

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
