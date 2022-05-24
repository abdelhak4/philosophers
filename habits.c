#include "philo.h"
/*
 ?  contains vars_init
 ?	is_eating and is_sleeping , is_thinking
 ?	and check_for_die
 */

void	is_eating(t_data *var, int ph)
{
	pthread_mutex_lock(&var->fork[var->s_ph[ph].l_fork]);
	print_msg(var, ph, "has taken the left fork", YELLOW);
	pthread_mutex_lock(&var->fork[var->s_ph[ph].r_fork]);
	print_msg(var, ph, "has taken the right  fork", YELLOW);
	var->s_ph[ph].last_eat = m_time() - var->start_t;
	print_msg(var, ph, "is eating", GREEN);
	//var->s_ph[ph].eat_times++;
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

int check_for_die(t_data *var)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < var->n_of_philo)
		{
			pthread_mutex_lock(&var->lock);
			if (m_time() - var->start_t - var->s_ph[i].last_eat >= var->time_to_die)
			{
				pthread_mutex_lock(&var->write);
				var->is_died = 1;
				printf("%s%ld ms {%d} \"%s\"\n", RED, (m_time() - var->start_t),
					   i + 1, " is died");
				usleep(100);
				return (1);
			}
			pthread_mutex_unlock(&var->lock);
			//usleep(400);
			i++;
		}
		i = 0;
	}
	return (0);
}
