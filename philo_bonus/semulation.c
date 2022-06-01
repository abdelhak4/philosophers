/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:07:09 by ael-mous          #+#    #+#             */
/*   Updated: 2022/06/01 16:07:12 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_usleep(time_t t)
{
	time_t	t0;

	t0 = m_time();
	while (m_time() - t0 < t)
		usleep(51);
}

time_t	m_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_msg(t_data *var, int ph, char *str, char *clr)
{
	sem_wait(var->lock);
	printf("%s%ld ms {%d} %s\n", clr, (m_time() - var->start_t), ph + 1, str);
	sem_post(var->lock);
}

void	is_eating(t_data *this, int ph)
{
	sem_wait(this->sem);
	print_msg(this, ph, "has taken the left fork", YELLOW);
	sem_wait(this->sem);
	print_msg(this, ph, "has taken the right  fork", YELLOW);
	sem_wait(this->var);
	this->last_eat = m_time() - this->start_t;
	sem_post(this->var);
	sem_wait(this->lock);
	print_msg(this, ph, "is eating", GREEN);
	sem_post(this->lock);
	/*var->s_ph[ph].eat_times++;*/
	my_usleep(this, this->time_to_eat);
	sem_post(this->sem);
	sem_post(this->sem);
}

void	is_sleeping(t_data *this, int ph)
{
	print_msg(this, ph, "is sleeping", PURPLE);
	my_usleep(this, this->time_to_sleep);
}

void	is_thinking(t_data *this, int ph)
{
	sem_wait(this->lock);
	print_msg(this, ph, "is thinking", CYAN);
	sem_post(this->lock);
}
