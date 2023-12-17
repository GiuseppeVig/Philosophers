/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:00:42 by gvigilan          #+#    #+#             */
/*   Updated: 2023/12/17 18:19:20 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

void	assign_forks(t_philo *phi, t_fork *forks, int i, t_data *info)
{
	phi->r_fork = &forks[i];
	if (i == 0)
		phi->l_fork = &forks[info->num_of_philosophers - 1];
	else
		phi->l_fork = &forks[i - 1];
}


void	init_philos(t_data *info)
{
	int		i;
	t_philo	*philos;

	i = 0;
	while (i < info->num_of_philosophers)
	{
		philos = info->phi + i;
		philos->id = i + 1;
		philos->n_of_meals = 0;
		philos->is_eating = 0;
		philos->is_full = 0;
		philos->data = info;
		assign_forks(philos, info->forks, i, info);
		pthread_mutex_init(&info->write, NULL);
		pthread_mutex_init(&info->lock, NULL);
		i++;
	}
}

void	inizialize_threads(t_data *info)
{
	int	i;
	
	info->phi = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philosophers);
	info->forks = (t_fork *)malloc(sizeof(t_fork) * info->num_of_philosophers);
	i = 0;
	while (i < info->num_of_philosophers)
	{
		pthread_mutex_init(&info->forks[i].fork, NULL);
		info->forks[i].id = i + 1;
		i++;
	}
	init_philos(info);
	pthread_mutex_init(&info->write, NULL);
	pthread_mutex_init(&info->lock, NULL);
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

int	main(int argc, char **argv)
{
	t_data	values;
	int i;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of values");
		exit(1);
	}
	get_data(argv, argc, &values);
	inizialize_threads(&values);
	i = 0;
	dinner_time(&values);
	while (i < values.num_of_philosophers)
	{
		pthread_join(values.phi[i].th, NULL);
		i++;
	}
	clear_data(&values);
	return (0);
}
