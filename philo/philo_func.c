/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:42:35 by gvigilan          #+#    #+#             */
/*   Updated: 2023/12/11 12:00:41 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *phi)
{
	pthread_mutex_lock(&phi->data->write);
	printf("Philosophers %d has taken the right fork\n", phi->id);
	pthread_mutex_lock(&phi->r_fork->fork);
	printf("Philosophers %d has taken the left fork\n", phi->id);
	pthread_mutex_lock(&phi->l_fork->fork);
	pthread_mutex_unlock(&phi->data->write);
}

void	sleeping(t_philo *phi)
{
	printf("Philosopher %d is sleeping\n", phi->id);
	usleep(phi->data->t_to_sleep);
	pthread_mutex_unlock(&phi->data->write);
}

void	eat(t_philo *phi)
{
	pthread_mutex_lock(&phi->data->write);
	phi->is_eating = 1;
	printf("Philosopher %d is eating\n", phi->id);
	usleep(phi->data->t_to_eat);
	phi->last_meal = timestamp();
	phi->n_of_meals++;
	phi->is_eating = 0;
	pthread_mutex_unlock(&phi->r_fork->fork);
	pthread_mutex_unlock(&phi->l_fork->fork);
	sleeping(phi);
}

void	think(t_philo *phi)
{
	pthread_mutex_lock(&phi->data->write);
	printf("Philosopher %d is thinking\n", phi->id);
	pthread_mutex_unlock(&phi->data->write);
}

void	clear_data(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->num_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	free(data->phi);
	free(data->forks);
}