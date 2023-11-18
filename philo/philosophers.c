/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:00:42 by gvigilan          #+#    #+#             */
/*   Updated: 2023/11/18 07:29:05 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

void	assign_forks(t_philo *phi, t_fork *forks, int i, t_data *info)
{
	if (phi->id % 2 == 0)
	{
		phi->r_fork = &forks[i]->fork;
		if (i == 0)
			phi->l_fork = &forks[info->num_of_philosophers]->fork;
		else
			phi->l_fork = &forks[i - 1]->fork;
	}
	else
	{
		phi->l_fork = &forks[i]->fork;
		if (i == 0)
			phi->r_fork = &forks[info->num_of_philosophers]->fork;
		else
			phi->r_fork = &forks[i - 1]->fork;
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
	}
}

void	*inizialize_threads(t_data *info)
{
	int	i;
	info->phi = malloc(sizeof(t_philo) * info->num_of_philosophers);
	info->forks = malloc(sizeof(t_fork) * info->num_of_philosophers);
	if (!info->phi || info->forks)
	{
		printf("Error: Philosophers must be more than 0\n");
		exit(1);
	}

	i = 0;
	while (i < info->num_of_philosophers)
	{
		pthread_mutex_init(&info->forks[i].fork, NULL);
		info->forks[i].id = i + 1;
	}
	init_philos(info);
	pthread_mutex_init(&info->write);
}

int	main(int argc, char **argv)
{
	t_data	values;
	int i = 0;
	t_philo *philos;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of values");
		exit(1);
	}
	if (argc == 5)
		get_data(argv, 0, &values);
	else if (argc == 6)
		get_data(argv, 1, &values);
	philos = inizialize_threads(&values);
	while (i < values.num_of_philosophers)
	{
		pthread_create(&philos[i].th, NULL, routine2, &philos[i]);
		i++;
	}
	i = 0;
	while (i < values.num_of_philosophers)
	{
		pthread_join(philos[i].th, NULL);
		i++;
	}
	return (0);
}
