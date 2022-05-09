/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 20 22/04/17 15:42:17 by ael-mous          #+#    #+#             */
/*   Updated: 2022/04/17 15:42:19 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int c = 0;
pthread_mutex_t  mutex;
void	*routine()
{
	int i = 0;
//	int c = *(int*)cd;
	while (i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		c++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return NULL;
}

int	main(int argc, char **argv)
{
	int i =0;
	pthread_t id[2];
	pthread_mutex_init(&mutex, NULL);
	while (i < 3)
	{
		pthread_create(id + i, NULL, &routine, &i);
		printf("thread is created %d\n" , i);
		i++;
	}
	for (int j = 0; j < 3; j++)
	{
		pthread_join(id[j], NULL);
		printf("thread is joind %d\n", j);
	}
	printf("%d\n", c);
	return (0);
}





