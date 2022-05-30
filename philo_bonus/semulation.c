
#include "philo_bonus.h"

void	my_usleep(t_data *var, time_t t)
{
	time_t	t0 = m_time();
	while (m_time() - t0 < t)
		usleep(51);
}

time_t	m_time()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec/1000));
}

void	print_msg(t_data *var, int ph, char *str, char *clr)
{
	printf("%s%ld ms {%d} \"%s\"\n",clr , (m_time() - var->start_t),
		   ph + 1, str);
}

void	is_eating(t_data *this, int ph)
{
	sem_wait(&this->sem[this->ph]);
	sem_wait(&this->sem[(this->ph + 1) % this->n_of_ph]);
	print_msg(this, ph, "has taken the left fork", YELLOW);
	print_msg(this, ph, "has taken the right  fork", YELLOW);
	//pthread_mutex_lock(&var->mut);
	//var->s_ph[ph].last_eat = m_time() - var->start_t;
	//pthread_mutex_unlock(&var->mut);
	print_msg(this, ph, "is eating", GREEN);
	//pthread_mutex_lock(&var->mut);
	//var->s_ph[ph].eat_times++;
	//pthread_mutex_unlock(&var->mut);
	my_usleep(this, this->time_to_eat);
	sem_post(&this->sem[this->ph]);
	sem_post(&this->sem[(this->ph + 1) % this->n_of_ph]);
}

void	is_sleeping(t_data *this, int ph)
{
	print_msg(this, ph, "is sleeping", PURPLE);
	my_usleep(this, this->time_to_sleep);
}

void	is_thinking(t_data *this, int ph)
{
	print_msg(this, ph, "is thinking", CYAN);
}