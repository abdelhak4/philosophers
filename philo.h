/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 15:42:32 by ael-mous          #+#    #+#             */
/*   Updated: 2022/04/17 15:42:34 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_ph_staffs
{
	int				n_of_philo;
	pthread_mutex_t	lock;
	pthread_mutex_t	*fork_lock;
	int 			state;
	struct timeval	time;

	time_t 			sec;
	time_t			ms;
	int				i;
	int 			die;
	unsigned long 	Start_t;
	unsigned long 	End_t;
	unsigned long 	t;
	int 			eat;
	int 			n_time_to_each_ph_to_eat;
	int 			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*forks;
	int				*ph;
}	t_data;
void	down_forks(t_data *var, int f_right, int f_left);
int		ft_atoi(const char *str);
void	printing_msg(t_data *var, int state, int ph);
unsigned long m_time(t_data *vars);

#endif