/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:42:35 by gvigilan          #+#    #+#             */
/*   Updated: 2023/11/18 04:46:15 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *phi)
{
	printf("Philosophers %d has taken the right fork", phi->id);
	pthread_mutex_lock(&phi->r_fork->fork);
	printf("Philosophers %d has taken the left fork", phi->id);
	pthread_mutex_lock(&phi->l_fork->fork);
}

void	sleep(t_philo *phi)
{
	pthread_mutex_unlock(&phi->r_fork->fork);
	pthread_mutex_unlock(&phi->l_fork->fork);
	printf("Philosopher %d is sleeping", phi->id);
	usleep(phi->info->t_to_sleep);
}

void	eat(t_philo *phi)
{
	pthread_mutex_lock(&phi->info->write);
	take_forks(phi);
	phi->is_eating = 1;
	printf("Philosopher %d is eating", phi->id);
	usleep(phi->info->t_to_eat);
	phi->last_meal = timestamp() + phi->info->t_of_death;
	phi->n_of_meals++;
	sleep(phi);
}
