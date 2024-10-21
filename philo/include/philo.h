/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:02:21 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/21 16:58:12 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define DIGIT_ONLY "All arguments must be digits only.\n"

# define WRONG_ARGS "This is how the program must be \
used: ./philos number_of_philosophers time_to_die \
time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]"

# define MALLOC_ERROR "Error found while allocing memory."

# define MUTEX_ERROR "Error found while initiating Mutex."

# define EATING "is eating"

# define THINKING "is thinking"

# define SLEEPING "is sleeping"

# define DIED "died"

# define FORKING "has taken a fork"

# define DEFORKING "has put down a fork"

# define FORK 0

# define EAT 1

# define SLEEP 2

# define DEFORK 3

# define DEAD 4

# define THINK 5

typedef struct s_stats
{
	long					nbr_philo;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					eat_times;
	pthread_mutex_t			mutex;
	bool					end;
}				t_stats;

typedef struct s_philo
{
	int					philo_id;
	int					num_eat;
	int					bi;
	suseconds_t			start_time;
	suseconds_t			last_meal;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			t_id;
	t_stats				*stats;
}			t_philo;

t_philo			*init_philos(t_stats *stats, pthread_mutex_t *forks);
pthread_mutex_t	*init_forks(t_stats *stats);

void			free_forks(pthread_mutex_t *forks, int end);
void			free_all(pthread_mutex_t *forks, t_stats *stats,
					t_philo *philo);
bool			shinu(pthread_mutex_t *forks, t_stats *stats,
					t_philo *philo, char *err);

bool			check_args(int argc, char **argv);
bool			check_is_digit(char **argv);
bool			check_max_int(char **argv);

long			ft_atol(const char *str);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *str);

bool			build_struct(char **argv, t_stats *philos);
bool			start_thread(t_stats *stats, t_philo *philo,
					pthread_mutex_t *fork);
void			*philo_life(void *v_philo);
void			print_status(t_philo *philo, char *status, int action);
bool			is_dead(t_philo *philo);
void			do_something(t_philo *philo, int action);
suseconds_t		get_time(void);
bool			monitoring(t_stats *stats, t_philo *philo);
bool			cycle(t_philo *philo);
bool			check_if_eaten(t_philo *philo);
void			pick_forks(t_philo *philo);
void			lay_forks(t_philo *philo);
void			wait_time(t_philo *philo, u_int64_t time);
bool			end_philo(t_stats *stats);

#endif