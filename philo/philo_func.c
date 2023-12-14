/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:42:35 by gvigilan          #+#    #+#             */
/*   Updated: 2023/12/14 14:55:45 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *phi)
{
	printf("Philosophers %d has taken the right fork\n", phi->id);
	pthread_mutex_lock(&phi->r_fork->fork);
	printf("Philosophers %d has taken the left fork\n", phi->id);
	pthread_mutex_lock(&phi->l_fork->fork);
}

void	take_forks2(t_philo *phi)
{
	printf("Philosophers %d has taken the left fork\n", phi->id);
	pthread_mutex_lock(&phi->l_fork->fork);
	printf("Philosophers %d has taken the right fork\n", phi->id);
	pthread_mutex_lock(&phi->r_fork->fork);
}

void	sleeping(t_philo *phi)
{
	pthread_mutex_unlock(&phi->r_fork->fork);
	pthread_mutex_unlock(&phi->l_fork->fork);
	printf("Philosopher %d is sleeping\n", phi->id);
	pthread_mutex_unlock(&phi->data->lock);
	usleep(phi->data->t_to_sleep);
}

void	think(t_philo *phi)
{
	pthread_mutex_lock(&phi->data->write);
	printf("Philosopher %d is thinking\n", phi->id);
	pthread_mutex_unlock(&phi->data->write);
}

void	eat(t_philo *phi)
{
	if (phi->data->end != 1)
	{
		pthread_mutex_lock(&phi->data->lock);
		pthread_mutex_lock(&phi->data->write);
		if (phi->id % 2 == 0)
			take_forks2(phi);
		else
			take_forks(phi);
		phi->is_eating = 1;
		phi->last_meal = timestamp();
		printf("Philosopher %d is eating\n", phi->id);
		usleep(phi->data->t_to_eat);
		phi->n_of_meals++;
		phi->is_eating = 0;
		sleeping(phi);
		pthread_mutex_unlock(&phi->data->write);
	}
}
