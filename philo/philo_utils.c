/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:08:05 by gvigilan          #+#    #+#             */
/*   Updated: 2023/12/17 17:32:47 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((int)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atoi(char *str)
{
	int	i;
	int	val;
	int	neg;

	i = 0;
	neg = 1;
	val = 0;
	while(str[i] == 32 || (str[i] > 8 && str[i] < 13))
		i++;
	while(str[i] >= '0' && str[i] < '9')
	{
		val += (str[i] - '0');
		if (str[i + 1] == '\0')
			return (val * neg);
		val *= 10;
		i++;
	}
	return (val * neg);
}

void	check_errors(char **args, int limit)
{
	int	i;
	int	j;
	int	check;

	i = 1;
	if (limit == 6)
		check = 5;
	else
		check = 4;
	while (i <= check)
	{
		j = 0;
		while (args[i][j])
		{
			if ((args[i][j] < '0' || args[i][j] > '9') || args[i][0] == '-')
			{
				printf("Error: Invalid value for argument");
				exit(1);
			}
			else
				j++;
		}
		i++;
	}
}

void	get_data(char **args, int limit, t_data *requests)
{
	check_errors(args, limit);
	requests->num_of_philosophers = ft_atoi(args[1]);
	requests->t_of_death = ft_atoi(args[2]);
	requests->t_to_eat = ft_atoi(args[3]) * 1000;
	requests->t_to_sleep = ft_atoi(args[4]) * 1000;
	if (limit == 6)
		requests->num_of_meals = ft_atoi(args[5]);
	else
		requests->num_of_meals = -1;
	requests->end = 0;
	requests->waiting = 1;
	requests->is_dead = 0;
}

void	wait_for_start(t_philo *phi)
{
	while (phi->data->waiting)
		;
}