/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:00:42 by gvigilan          #+#    #+#             */
/*   Updated: 2023/09/22 10:51:09 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine2(void *args)
{
	t_philo	*aldo = (t_philo *)args;

	gettimeofday(&tm, &tz);
	while (!aldo->dead && aldo->n_of_meals < aldo->informations.num_of_meals)
	{
		if (tm.tv_usec - aldo->last_meal> aldo->informations.t_of_death)
		{
			printf("Philosopher %d is fucking dead\n", aldo->philo_id);
			exit(0);
		}
		if (!pthread_mutex_lock(aldo->left->forchetta) && !pthread_mutex_lock(aldo->right->forchetta))
		{
			pthread_mutex_unlock(&aldo->write);
			printf("Philosopher %d is eating\n", aldo->philo_id);
			aldo->n_of_meals++;
			aldo->last_meal = tm.tv_usec;
			printf("Philosopher %d is sleeping\n", aldo->philo_id);
			usleep(aldo->informations.t_to_sleep);
		}
		else if (pthread_mutex_lock(&aldo->write))
			printf("Philosopher %d is thinking\n", aldo->philo_id);
		pthread_mutex_unlock(aldo->left->forchetta);
		pthread_mutex_unlock(aldo->right->forchetta);
	}
	return (aldo);
}

void	*routine(void *args)
{
	t_philo	*aldo = (t_philo *)args;
	gettimeofday(&tm, &tz);
	while (!aldo->dead)
	{
		if (tm.tv_usec - aldo->last_meal > aldo->informations.t_of_death)
		{
			printf("Philosopher %d is fucking dead\n", aldo->philo_id);
			exit(1);
		}
		if (!pthread_mutex_lock(aldo->left->forchetta) && !pthread_mutex_lock(aldo->right->forchetta))
		{
			printf("Philosopher %d is eating\n", aldo->philo_id);
			aldo->last_meal = tm.tv_usec;
			usleep(aldo->informations.t_to_eat);
			pthread_mutex_unlock(&aldo->write);
			printf("Philosopher %d is sleeping\n", aldo->philo_id);
			usleep(aldo->informations.t_to_sleep);
		}
		else if (pthread_mutex_lock(&aldo->write))
			printf("Philosopher %d is thinking\n", aldo->philo_id);
		pthread_mutex_unlock(aldo->left->forchetta);
		pthread_mutex_unlock(aldo->right->forchetta);
	}
	return (aldo);
}

void	inizialize_threads(t_data info)
{
	int	i;
	t_philo	*guests = (t_philo *)malloc(sizeof(t_philo) * info.num_of_philosophers);
	t_fork	*forks = (t_fork *)malloc(sizeof(t_fork) * info.num_of_philosophers);

	i = 0;
	gettimeofday(&tm, &tz);
	while (i < info.num_of_philosophers)
	{
		guests[i].dead = 0;
		guests[i].philo_id = i + 1;
		guests[i].n_of_meals = 0;
		guests[i].left->forchetta = forks[i].forchetta;
		if (i == info.num_of_philosophers - 1)
			guests[i].right->forchetta = forks[0].forchetta;
		else
			guests[i].right->forchetta = forks[i + 1].forchetta;
		guests[i].last_meal = tm.tv_usec;
		pthread_mutex_init(guests[i].left->forchetta, NULL);
		pthread_mutex_init(guests[i].right->forchetta, NULL);
		if (info.num_of_meals != 0)
			pthread_create(&guests[i].id, NULL, *routine, (&guests[i]));
		else
			pthread_create(&guests[i].id, NULL, *routine2, (&guests[i]));
	}
}

int	main(int argc, char **argv)
{
	t_data	values;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of values");
		exit(1);
	}
	if (argc == 5)
		values = get_data(argv, 0);
	else if (argc == 6)
		values = get_data(argv, 1);
	inizialize_threads(values);
	return (0);
}
