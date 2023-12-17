/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:42:35 by gvigilan          #+#    #+#             */
/*   Updated: 2023/12/17 19:27:13 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *phi)
{
	pthread_mutex_lock(&phi->data->write);
	if (!phi->data->end)
	{
		if (phi->id % 2 == 0)
		{
			pthread_mutex_lock(&phi->r_fork->fork);
			printf("Philosopher %d has taken the right fork\n", phi->id);
			pthread_mutex_lock(&phi->l_fork->fork);
			printf("Philosopher %d has taken the left fork\n", phi->id);
		}
		else
		{
			pthread_mutex_lock(&phi->l_fork->fork);
			printf("Philosopher %d has taken the left fork\n", phi->id);
			pthread_mutex_lock(&phi->r_fork->fork);
			printf("Philosopher %d has taken the right fork\n", phi->id);
		}
	}
	pthread_mutex_unlock(&phi->data->write);
}

void	sleeping(t_philo *phi)
{
	pthread_mutex_lock(&phi->data->write);
	if (!phi->data->end)
	{
		printf("Philosopher %d is sleeping\n", phi->id);
		usleep(phi->data->t_to_sleep);
	}
	pthread_mutex_unlock(&phi->data->write);
}

void	think(t_philo *phi)
{
	pthread_mutex_lock(&phi->data->write);
	if (!phi->data->end)
		printf("Philosopher %d is thinking\n", phi->id);
	pthread_mutex_unlock(&phi->data->write);
}

void	eat(t_philo *phi)
{
	if (phi->data->end != 1)
	{
		if (timestamp() - phi->last_meal >= phi->data->t_of_death && phi->is_eating == 0)
		{
			pthread_mutex_lock(&phi->data->write);
			if (phi->data->end == 0)
				printf("Philosopher %d is dead\n", phi->id);
			phi->data->end = 1;
			return ;
		}
		if (!phi->data->end)
		{
			digest(phi);
			sleeping(phi);
			think(phi);
		}
		else
			return ;
	}
}

void	digest(t_philo *phi)
{
	take_forks(phi);
	pthread_mutex_lock(&phi->data->lock);
	phi->n_of_meals++;
	phi->is_eating = 1;
	phi->last_meal = timestamp();
	pthread_mutex_unlock(&phi->data->lock);
	pthread_mutex_lock(&phi->data->write);
	if (!phi->data->end)
		printf("Philosopher %d is eating\n", phi->id);
	pthread_mutex_unlock(&phi->data->write);
	usleep(phi->data->t_to_eat);
	pthread_mutex_unlock(&phi->r_fork->fork);
	pthread_mutex_unlock(&phi->l_fork->fork);
	phi->is_eating = 0;
}
