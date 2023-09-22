/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:08:05 by gvigilan          #+#    #+#             */
/*   Updated: 2023/09/20 06:12:49 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	while(str[i] > '0' && str[i] < '9')
	{
		val += (str[i] - '0');
		val *= 10;
		i++;
	}
	return (val * neg);
}

t_data	get_data(char **args, int limit)
{
	t_data	requests;

	requests.num_of_philosophers = ft_atoi(args[1]);
	requests.t_of_death = ft_atoi(args[2]);
	requests.t_to_eat = ft_atoi(args[3]);
	requests.t_to_sleep = ft_atoi(args[4]);
	if (limit)
		requests.num_of_meals = ft_atoi(args[5]);
	return (requests);
}

