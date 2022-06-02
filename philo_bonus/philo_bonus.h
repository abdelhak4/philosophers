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

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdatomic.h>
# define RED "\033[0;31m"
# define YELLOW "\e[1;33m"
# define CYAN "\e[0;36m"
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"

typedef struct s_ph_staffs
{
	int				n_of_ph;
	time_t			start_t;
	size_t			n_time_to_each_ph_to_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			r_fork;
	atomic_size_t	is_died;
	size_t			l_fork;
	size_t			eat;
	sem_t			*sem;
	sem_t			*var;
	sem_t			*lock;
	size_t			eat_times;
	size_t			ph;
	atomic_size_t	last_eat;
}	t_data;

	/****************************************************
	!***********	F U N C T I O N S	*****************
	*****************************************************/

void	my_usleep(time_t t);
void	parsing(t_data **vars, char **av, int ac);
int		ft_atoi(const char *str);
void	print_msg(t_data *var, int ph, char *str, char *clr);
time_t	m_time(void);
void	check_for_die(t_data *var);
void	is_sleeping(t_data *var, int ph);
void	is_eating(t_data *var, int ph);

#endif