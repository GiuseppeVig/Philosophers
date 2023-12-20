/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:42:35 by gvigilan          #+#    #+#             */
/*   Updated: 2023/12/20 11:17:01 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *phi)
{
	if (!phi->data->end)
	{
		if (phi->id % 2 == 0)
		{
			pthread_mutex_lock(&phi->r_fork->fork);
			philo_msg(phi, "has taken a fork", 1);
			pthread_mutex_lock(&phi->l_fork->fork);
			philo_msg(phi, "has taken a fork", 1);
		}
	}
}

void	eat(t_philo *phi)
{
	if (phi->data->end != 1)
	{
		if (!phi->data->end && timestamp() - phi->last_meal <= phi->data->t_of_death)
			digest(phi);
		else
		{
			if (phi->data->end == 0)
				philo_msg(phi, "is dead", 0);
			phi->data->end = 1;
		}
	}
}

void	digest(t_philo *phi)
{
	if (timestamp() - phi->last_meal >= phi->data->t_of_death)
	{
		if (phi->data->end == 0)
			philo_msg(phi, "is dead", 0);
		phi->data->end = 1;
	}
	else if (timestamp() - phi->last_meal < phi->data->t_of_death)
	{
		phi->is_eating = 1;
		phi->n_of_meals++;
		phi->last_meal = timestamp();
		philo_msg(phi, "is eating", 1);
		usleep(phi->data->t_to_eat);
		phi->is_eating = 0;
		drop_forks(phi);
		philo_msg(phi, "is sleeping", 1);
		usleep(phi->data->t_to_sleep);
	}
	else
		drop_forks(phi);
}


void	drop_forks(t_philo *phi)
{
	pthread_mutex_unlock(&phi->r_fork->fork);
	pthread_mutex_unlock(&phi->l_fork->fork);
}

void	philo_msg(t_philo *phi, char *msg, int unlock)
{
	pthread_mutex_lock(&phi->data->write);
	if (!phi->data->end)
	{
		printf("%d   Philosopher %d %s\n",timestamp() - phi->data->start,
			       phi->id, msg);
	}
	if (unlock)
		pthread_mutex_unlock(&phi->data->write);
}
