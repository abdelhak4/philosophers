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
# include <unistd.h>
# define Red "\033[0;31m"
# define Yellow "\e[1;33m"
# define Cyan "\e[0;36m"
# define Green "\033[0;32m"
# define Purple "\033[0;35m"

typedef struct philosophers
{
	int 			r_fork;
	int 			l_fork;
	int 			eat;
	int 			eat_times;
	int				ph;
	time_t			last_eat;
	time_t			t;

}	t_ph;

typedef struct s_ph_staffs
{
	pthread_mutex_t	lock;
	int				n_of_philo;
	int				i;
	time_t			Start_t;
	pthread_mutex_t	write;
	int 			die;
	int 			n_time_to_each_ph_to_eat;
	int 			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*fork;
	t_ph			*s_ph;
}	t_data;

void	my_usleep(t_data *var, time_t t);
t_ph 	vars_init(t_data *vars, int i);
void	parsing(t_data **vars, char **av, int ac);
int		ft_atoi(const char *str);
void	print_msg(t_data *var, int ph, char *str, char *clr);
time_t	m_time();
int		check_for_die(t_data *var);
void	is_thinking(t_data *var, int ph);
void	is_sleeping(t_data *var, int ph);
void	is_eating(t_data *var, int ph);

#endif