/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 07:18:04 by gvigilan          #+#    #+#             */
/*   Updated: 2023/12/20 11:21:20 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*special_case(void *data)
{
	t_philo	*philos;

	philos = (t_philo *)data;
	philos->last_meal = timestamp();
	pthread_create(&philos->death, NULL, death, philos);
	philo_msg(philos, "is thinking", 1);
	while (!philos->data->end)
		usleep(10);
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philos;

	philos = (t_philo *)data;
	philos->last_meal = timestamp();
	wait_for_start(philos);
	if (philos->id % 2 != 0)
		ft_usleep(100);
	pthread_create(&philos->death, NULL, death, philos);
	while (philos->data->end != 1 && !philos->is_full)
	{
		take_forks(philos);
		eat(philos);
		philo_msg(philos, "is thinking", 1);
		if (philos->n_of_meals == philos->data->num_of_meals)
			philos->is_full = 1;
		if (philos->data->end == 1)
		{
			pthread_mutex_unlock(&philos->data->write);
			drop_forks(philos);
		}
	}
	return (NULL);
}

void	*death(void *data)
{
	t_philo	*philos;

	philos = (t_philo *)data;
	while (philos->data->end != 1 && !philos->is_full)
	{
		if ((philos->data->end
				|| timestamp() - philos->last_meal > philos->data->t_of_death)
			&& philos->is_eating != 1)
		{
			if (philos->data->end == 0)
				philo_msg(philos, "died", 0);
			philos->data->end = 1;
			pthread_mutex_unlock(&philos->data->write);
			return (NULL);
		}
	}
	return (NULL);
}

void	dinner_time(t_data *info)
{
	int	i;

	i = 0;
	if (info->num_of_meals == 0)
		return ;
	if (info->num_of_philosophers == 1)
	{
		pthread_create(&info->phi[i].th, NULL, special_case, &info->phi[i]);
		info->start = timestamp();
	}
	else
	{
		while (i < info->num_of_philosophers)
		{
			pthread_create(&info->phi[i].th, NULL, routine, &info->phi[i]);
			i++;
		}
		info->start = timestamp();
		info->waiting = 0;
	}
}

void	ft_usleep(int time)
{
	int	start;

	start = timestamp();
	while (timestamp() - start < time)
		usleep(10);
}
