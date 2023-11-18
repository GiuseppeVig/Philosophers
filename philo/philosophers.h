/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:12:17 by gvigilan          #+#    #+#             */
/*   Updated: 2023/11/18 07:00:26 by gvigilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>

typedef struct	s_fork
{
	pthread_mutex_t fork;
	int				id;
} t_fork;

typedef struct	s_philosophers
{
	pthread_t 		th;
	int				id;	
	int				n_of_meals;
	int				last_meal;
	int				is_full;
	int				is_eating;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_data			*data;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
} t_philo;

typedef struct s_data
{
	int	num_of_philosophers;
	int	t_of_death;
	int	t_to_eat;
	int	t_to_sleep;
	int	num_of_meals;
	int	end;
	t_philo	*phi;
	t_fork	*forks;
	pthread_mutex_t		write;
	pthread_mutex_t		lock;
}	t_data;


t_data	get_data(char **args, int limit);
void	*routine(void *args);
void	*routine2(void *args);
t_philo	*inizialize_threads(t_data *info);
int		ft_atoi(char *str);
int	timestamp(void);


#endif
