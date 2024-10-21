/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:30:23 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/21 17:02:12 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

bool	start_thread(t_stats *stats, t_philo *philo, pthread_mutex_t *fork)
{
	int			i;
	suseconds_t	time;

	i = -1;
	time = get_time();
	while (++i < stats->nbr_philo)
	{
		philo[i].start_time = time;
		if (pthread_create(&philo[i].t_id, NULL,
				&philo_life, (void *)&philo[i]))
			return (shinu(fork, NULL, philo, MALLOC_ERROR));
	}
	i = -1;
	monitoring(stats, philo);
	while (++i < stats->nbr_philo)
	{
		if (pthread_join(philo[i].t_id, NULL))
			return (shinu(fork, NULL, philo, MALLOC_ERROR));
	}
	return (true);
}

bool	monitoring(t_stats *stats, t_philo *philo)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (true)
	{
		while (++i < stats->nbr_philo)
		{
			if (stats->eat_times != -1)
				if (check_if_eaten(&philo[i]))
					++j;
			if (j == stats->nbr_philo && stats->eat_times != -1)
				return (end_philo(stats));
			if (stats-> end == false && is_dead(&philo[i]))
			{
				end_philo(stats);
				print_status(&philo[i], DIED, DEAD);
				return (true);
			}
		}
		i = -1;
	}
	return (true);
}

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->stats->mutex);
	if (philo->stats->end == false
		&& get_time() - philo->last_meal > philo->stats->time_to_die)
	{
		philo->stats->end = true;
		pthread_mutex_unlock(&philo->stats->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->stats->mutex);
	return (false);
}

bool	check_if_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->stats->mutex);
	if (philo->stats->eat_times != -1)
	{
		if (philo->num_eat >= philo->stats->eat_times && philo->bi == 0)
		{
			philo->bi = 1;
			pthread_mutex_unlock(&philo->stats->mutex);
			return (true);
		}
	}
	pthread_mutex_unlock(&philo->stats->mutex);
	return (false);
}
