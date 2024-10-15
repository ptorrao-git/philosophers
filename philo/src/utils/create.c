/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:30:23 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/15 15:35:06 by ptorrao-         ###   ########.fr       */
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
	int	i;

	i = -1;
	while (++i < stats->nbr_philo)
	{
		philo[i].start_time = get_time();
		if (pthread_create(&philo[i].t_id, NULL,
				&philo_life, (void *)&philo[i]))
			return (shinu(fork, NULL, philo, MALLOC_ERROR));
	}
	monitoring(stats, philo);
	i = -1;
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

	j = 0;
	while (true)
	{
		i = -1;
		pthread_mutex_lock(&philo->stats->mutex);
		while (++i < stats->nbr_philo)
		{
			if (stats-> end == false && is_dead(&philo[i]))
				return (stats->end = true,
					pthread_mutex_unlock(&philo->stats->mutex),
					print_status(&philo[i], DIED, DEAD), true);
			if (stats->eat_times != -1)
				if (check_if_eaten(&philo[i]))
					++j;
			if (j == stats->nbr_philo && stats->eat_times != -1)
				return (stats->end = true,
					pthread_mutex_unlock(&philo->stats->mutex));
		}
		pthread_mutex_unlock(&philo->stats->mutex);
	}
	return (true);
}

bool	is_dead(t_philo *philo)
{
	if (philo->stats->end == false
		&& get_time() - philo->last_meal > philo->stats->time_to_die)
	{
		philo->stats->end = true;
		return (true);
	}
	return (false);
}

bool	check_if_eaten(t_philo *philo)
{
	if (philo->stats->eat_times != -1)
	{
		if (philo->num_eat >= philo->stats->eat_times && philo->bi == 0)
		{
			philo->bi = 1;
			return (true);
		}
	}
	return (false);
}
