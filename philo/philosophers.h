/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigilan <gvigilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:12:17 by gvigilan          #+#    #+#             */
/*   Updated: 2023/09/20 06:46:33 by gvigilan         ###   ########.fr       */
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

struct timeval tm;
struct timezone tz;

typedef struct	s_fork
{
	pthread_mutex_t	*forchetta;
	int				locked;
}				t_fork;


typedef struct data
{
	int	num_of_philosophers;
	int	t_of_death;
	int	t_to_eat;
	int	t_to_sleep;
	int	num_of_meals;
}	t_data;

typedef struct	philosophers
{
	pthread_t id;
	int					last_meal;
	int					philo_id;
	int					timetodie;
	int					n_of_meals;
	int					dead;
	t_fork				*left;
	t_fork				*right;
	t_data				informations;
	pthread_mutex_t		write;
} t_philo;

t_data	get_data(char **args, int limit);
void	*routine(void *args);
void	*routine2(void *args);
void	inizialize_threads(t_data info);
int		ft_atoi(char *str);
t_data	get_data(char **args, int limit);


#endif
