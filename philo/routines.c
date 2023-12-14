/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 07:18:04 by gvigilan          #+#    #+#             */
/*   Updated: 2023/12/14 14:56:33 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	special_case(t_data *info)
{
	printf("Philosospher %d is dead\n", info->phi->id);
}

void	*routine(void *data)
{
	t_philo	*philos;

	philos = (t_philo *)data;
	wait_for_start(philos);
	philos->last_meal = timestamp();
	while (philos->data->end == 0 && !philos->is_full)
	{
		think(philos);
		if (timestamp() - philos->last_meal >= philos->data->t_of_death && philos->is_eating == 0)
		{
			pthread_mutex_lock(&philos->write);
			printf("Philosospher %d is dead\n", philos->id);
			philos->data->end = 1;
			pthread_mutex_lock(&philos->lock);
			return (NULL);
		}
		if (!philos->is_full && philos->data->end != 1)
			eat(philos);
		if (philos->n_of_meals == philos->data->num_of_meals)
			philos->is_full = 1;
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
