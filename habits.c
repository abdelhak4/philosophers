#include "philo.h"
/*
 ?  contains vars_init
 ?	is_eating and is_sleeping , is_thinking
 ?	and check_for_die
 */

void died(t_data *var, int i)
{
	time_t	result;
	//pthread_mutex_lock(&var->lock);
	//printf("last eat %ld	m_time %ld	result %ld\n",var->s_ph[i].last_eat,\
		   var->start_t, result);
	result = m_time() - var->s_ph[i].last_eat;
		   printf("result = %ld i %d\n", result, i+1);
	if (result >= var->time_to_die)
	{
		var->is_died = 1;
//		usleep(100);
	}

}

void	is_eating(t_data *var, int ph)
{
	pthread_mutex_lock(&var->fork[var->s_ph[ph].l_fork]);
	print_msg(var, ph, "has taken the left fork", YELLOW);
	pthread_mutex_lock(&var->fork[var->s_ph[ph].r_fork]);
	print_msg(var, ph, "has taken the right  fork", YELLOW);
	print_msg(var, ph, "is eating", GREEN);
	//var->s_ph[ph].eat_times++;
	var->s_ph[ph].last_eat = m_time();
	my_usleep(var, var->time_to_eat);
	var->s_ph[ph].eat = 1;
	pthread_mutex_unlock(&var->fork[var->s_ph[ph].l_fork]);
	pthread_mutex_unlock(&var->fork[var->s_ph[ph].r_fork]);

}

void	is_sleeping(t_data *var, int ph)
{
	print_msg(var, ph, "is sleeping", PURPLE);
	my_usleep(var, var->time_to_sleep);
}

void	is_thinking(t_data *var, int ph)
{
	print_msg(var, ph, "is thinking", CYAN);
}

void 	check_for_die(t_data *var)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < var->n_of_philo)
		{
			died(var, i);
			if (var->is_died == 1)
			{
				print_msg(var, i, "is died", RED);
				return;
			}
			i++;
		}
		i = 0;
	}
}
