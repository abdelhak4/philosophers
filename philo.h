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
#include <sys/time.h>
# include <stdlib.h>

typedef struct s_ph_staffs
{
	time_t 	sec;
	time_t	ms;
	int	n_of_philo;
	int time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int state;
	int	forks;
	struct timeval time;
	int	*ph;
}	t_data;
int	ft_isdigit(int c);

#endif