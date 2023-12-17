/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:42:35 by gvigilan          #+#    #+#             */
/*   Updated: 2023/12/17 17:55:09 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *phi)
{
	if (!phi->data->is_dead)
	{
		if (phi->id % 2 == 0)
		{
			pthread_mutex_lock(&phi->data->write);
			pthread_mutex_lock(&phi->r_fork->fork);
			printf("Philosopher %d has taken the right fork\n", phi->id);
			pthread_mutex_lock(&phi->l_fork->fork);
			printf("Philosopher %d has taken the left fork\n", phi->id);
			pthread_mutex_unlock(&phi->data->write);
		}
		else
		{
			pthread_mutex_lock(&phi->data->write);
			pthread_mutex_lock(&phi->l_fork->fork);
			printf("Philosopher %d has taken the left fork\n", phi->id);
			pthread_mutex_lock(&phi->r_fork->fork);
			printf("Philosopher %d has taken the right fork\n", phi->id);
			pthread_mutex_unlock(&phi->data->write);
		}
	}
	else
		return ;
}

void	sleeping(t_philo *phi)
{
	if (!phi->data->is_dead)
	{	
		pthread_mutex_lock(&phi->data->write);
		printf("Philosopher %d is sleeping\n", phi->id);
		pthread_mutex_unlock(&phi->data->write);
		usleep(phi->data->t_to_sleep);
	}
	else
		return ;
}

void	think(t_philo *phi)
{
	if (!phi->data->is_dead)
	{
		pthread_mutex_lock(&phi->data->write);
		printf("Philosopher %d is thinking\n", phi->id);
		pthread_mutex_unlock(&phi->data->write);
	}
	else
		return ;
}

void	eat(t_philo *phi)
{
	if (phi->data->end != 1)
	{
		if (timestamp() - phi->last_meal >= phi->data->t_of_death)
		{
			phi->data->is_dead = 1 ;
			return ;
		}
		if (!phi->data->is_dead)
		{
			take_forks(phi);
			phi->is_eating = 1;
			phi->last_meal = timestamp();
			printf("Philosopher %d is eating\n", phi->id);
			usleep(phi->data->t_to_eat);
			phi->n_of_meals++;
			phi->is_eating = 0;
			pthread_mutex_unlock(&phi->r_fork->fork);
			pthread_mutex_unlock(&phi->l_fork->fork);
			sleeping(phi);
			think(phi);
		}
		else
			return ;
	}
}

// void	die(t_philo *phi, t_data *info)
// {
	
// }
