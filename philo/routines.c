/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 07:18:04 by gvigilan          #+#    #+#             */
/*   Updated: 2023/11/18 08:59:31 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *data)
{
	t_philo	*philos;

	wait_for_start(philos);
	philos->last_meal = timestamp();
	while (philos->data->end == 0 && philos->n_of_meals 
		!= philos->data->num_of_meals)
	{
		if (timestamp() >= philos->data->t_of_death && philos->is_eating == 0)
		{
			printf("Philosospher %d is dead\n", philos->id);
			philos->data->end = 1;
		}
		take_forks(philos);
		eat(philos);
		sleep(philos);
		think(philos);
		if (philos->n_of_meals == philos->data->num_of_meals)
			philos->is_full == 1;
	}
	return (NULL);
}

void	dinner_time(t_data *info)
{
	int	i;

	i = 0;
	if (info->num_of_meals == 0)
		return ;
	else if (info->num_of_philosophers == 1)
		return ;
	else 
	{
		while (i < info->num_of_philosophers)
		{
			pthread_create(&info->phi[i].th, NULL, routine, NULL);
			i++;
		}
		info->start = timestamp();
		info->waiting = 0;
	}
}
