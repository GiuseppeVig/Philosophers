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

void	special_case(t_data *info)
{
	printf("Philosospher %d has taken a fork\n", info->phi->id);
	usleep(info->t_of_death * 1000);
	printf("Philosospher %d is dead\n", info->phi->id);
}

void	*routine(void *data)
{
	t_philo	*philos;

	philos = (t_philo *)data;
	philos->last_meal = timestamp();
	wait_for_start(philos);
	if (philos->id % 2 != 0)
		usleep(10);
	pthread_create(&philos->death, NULL, death, philos);
	while (philos->data->end != 1 && !philos->is_full)
	{
		philo_msg(philos, "is thinking", 1);
		take_forks(philos);
		eat(philos);
		if (philos->n_of_meals == philos->data->num_of_meals)
			philos->is_full = 1;
		if (philos->data->end == 1)
			pthread_mutex_unlock(&philos->data->write);
	}
	return (NULL);
}

void	*death(void *data)
{
	t_philo	*philos;

	philos = (t_philo *)data;
	while (philos->data->end != 1 && !philos->is_full)
	{
		if (philos->data->end || timestamp() - philos->last_meal > philos->data->t_of_death)
		{
			if (philos->data->end == 0)
				philo_msg(philos, "is dead", 0);
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
		special_case(info);
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
