/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:02:21 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/09/25 16:09:55 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdbool.h>

#define DIGIT_ONLY "All arguments must be digits only."

#define WRONG_ARGS "Error: this is how the program must be \
used: ./philos number_of_philosophers time_to_die \
time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]"

#define MALLOC_ERROR "Error found while allocing memory."

#define MUTEX_ERROR "Error found while initiating Mutex."
				
typedef struct s_stats
{
	int					nbr_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_times;
	pthread_mutex_t		mutex;
	bool				end;
}				t_stats;

typedef struct s_philo
{
	int					philo_id;
	int					num_eat;
	suseconds_t			start;
	suseconds_t			last_meal;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			t_id;
	t_stats				*stats;
}			t_philo;

t_philo			*init_philos(t_stats *stats, pthread_mutex_t *forks);
pthread_mutex_t	*init_forks(t_stats *stats);

void	free_forks(pthread_mutex_t *forks, int end);
void	free_all(pthread_mutex_t *forks, t_stats *stats, t_philo *philo);


bool	check_args(int	argc, char **argv);
/* bool	check_is_digit(char **argv); */

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);

bool	build_struct(char **argv, t_stats *philos);
suseconds_t	get_time(void);
void	shinu(pthread_mutex_t *forks, t_stats *stats, t_philo *philo, char *error);

#endif