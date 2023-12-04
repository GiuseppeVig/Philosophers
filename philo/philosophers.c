/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:00:42 by gvigilan          #+#    #+#             */
/*   Updated: 2023/12/04 04:10:24 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

void	assign_forks(t_philo *phi, t_fork *forks, int i, t_data *info)
{
	if (phi->id % 2 == 0)
	{
		phi->r_fork = &forks[i];
		if (i == 0)
			phi->l_fork = &forks[info->num_of_philosophers];
		else
			phi->l_fork = &forks[i - 1];
	}
	else
	{
		phi->l_fork = &forks[i];
		if (i == 0)
			phi->r_fork = &forks[info->num_of_philosophers];
		else
			phi->r_fork = &forks[i - 1];
	}
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

	info->phi = malloc(sizeof(t_philo *) * info->num_of_philosophers);
	info->forks = malloc(sizeof(t_fork *) * info->num_of_philosophers);
	i = 0;
	pthread_mutex_init(&info->write, NULL);
	pthread_mutex_init(&info->lock, NULL);
	while (i < info->num_of_philosophers)
	{
		pthread_mutex_init(&info->forks[i].fork, NULL);
		info->forks[i].id = i + 1;
		i++;
	}
	init_philos(info);
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
	if (argc == 5)
		get_data(argv, 0, &values);
	else if (argc == 6)
		get_data(argv, 1, &values);
	inizialize_threads(&values);
	i = 0;
	dinner_time(&values);
	while (i < values.num_of_philosophers)
	{
		pthread_join(values.phi[i].th, NULL);
		i++;
	}
	return (0);
}
