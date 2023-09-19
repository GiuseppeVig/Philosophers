/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:00:42 by gvigilan          #+#    #+#             */
/*   Updated: 2023/09/17 10:23:55 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine2(t_philo aldo, t_data time)
{
		gettimeofday(&tv, NULL);
	while (!aldo.dead && aldo.n_of_meals < time.num_of_meals)
	{
		if (tv.tv_usec - aldo.last_meal > time.t_of_death)
		{
			printf("Philosopher %d is fucking dead\n", aldo.philo_id);
			exit(1);
		}
		if (!pthread_mutex_lock(&aldo.left) && !pthread_mutex_lock(&aldo.right))
		{
			printf("Philosopher %d is eating\n", aldo.philo_id);
			aldo.n_of_meals++;
			aldo.last_meal = tv.tv_usec;
			usleep(time.t_to_eat);
		}
		else
			printf("Philosopher %d is thinking\n", aldo.philo_id);
		pthread_mutex_unlock(&aldo.left);
		pthread_mutex_unlock(&aldo.right);
		printf("Philosopher %d is sleeping\n", aldo.philo_id);
		usleep(time.t_to_sleep);
	}
}

void	*routine(t_philo aldo, t_data time)
{
	gettimeofday(&tv, NULL);
	while (!aldo.dead)
	{
		if (tv.tv_usec - aldo.last_meal > time.t_of_death)
		{
			printf("Philosopher %d is fucking dead\n", aldo.philo_id);
			exit(1);
		}
		if (!pthread_mutex_lock(&aldo.left) && !pthread_mutex_lock(&aldo.right))
		{
			printf("Philosopher %d is eating\n", aldo.philo_id);
			aldo.last_meal = tv.tv_usec;
			usleep(time.t_to_eat);
		}
		else
			printf("Philosopher %d is thinking\n", aldo.philo_id);
		pthread_mutex_unlock(&aldo.left);
		pthread_mutex_unlock(&aldo.right);
		printf("Philosopher %d is sleeping\n", aldo.philo_id);
		usleep(time.t_to_sleep);
	}
}

void	inizialize_threads(t_data info)
{
	int	i;
	t_philo			guests[info.num_of_philosophers];
	pthread_mutex_t	forks[info.num_of_philosophers];

	i = 0;
	gettimeofday(&tv, NULL);
	while (i < info.num_of_philosophers)
	{
		guests[i].dead = 0;
		guests[i].philo_id = i + 1;
		guests[i].n_of_meals = 0;
		guests[i].left = forks[i];
		if (i == info.num_of_philosophers - 1)
			guests[i].right = forks[0];
		else
			guests[i].right = forks[i + 1];
		guests[i].last_meal = tv.tv_usec;
		pthread_mutex_init(&guests[i].left, NULL);
		pthread_mutex_init(&guests[i].right, NULL);
		if (info.num_of_meals != 0)
			pthread_create(&guests[i].id, NULL, *routine, (&guests[i], &info));
		else
			pthread_create(&guests[i].id, NULL, *routine2, (&guests[i], &info));
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
		values = get_data(**argv, 0);
	else if (argc == 6)
		values = get_data(**argv, 1);
	start(values);
	inizialize_threads(values);
	return (0);
}
