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
		pthread_mutex_lock(&phi->r_fork->fork);
		philo_msg(phi, "has taken a fork", 1);
		pthread_mutex_lock(&phi->l_fork->fork);
		philo_msg(phi, "has taken a fork", 1);
	}
}

void	eat(t_philo *phi)
{
	if (phi->data->end != 1)
	{
		if (!phi->data->end
			&& timestamp() - phi->last_meal <= phi->data->t_of_death)
			digest(phi);
	}
}

void	digest(t_philo *phi)
{
	if (phi->data->end != 1)
	{
		phi->is_eating = 1;
		phi->last_meal = timestamp();
		phi->n_of_meals++;
		philo_msg(phi, "is eating", 1);
		ft_usleep(phi->data->t_to_eat / 1000);
		drop_forks(phi);
		phi->is_eating = 0;
		philo_msg(phi, "is sleeping", 1);
		ft_usleep(phi->data->t_to_sleep / 1000);
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
		printf("%d %d %s\n", timestamp() - phi->data->start,
			phi->id, msg);
	}
	if (unlock)
		pthread_mutex_unlock(&phi->data->write);
}
