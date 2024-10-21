/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:52:03 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/21 16:38:01 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_stats *stats, pthread_mutex_t *forks)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(stats->nbr_philo * sizeof(t_philo));
	if (!philo)
		shinu(forks, stats, philo, MALLOC_ERROR);
	while (++i < stats->nbr_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].num_eat = 0;
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % stats->nbr_philo];
		philo[i].last_meal = get_time();
		philo[i].stats = stats;
		philo[i].bi = 0;
	}
	return (philo);
}

pthread_mutex_t	*init_forks(t_stats *stats)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(stats->nbr_philo * sizeof(pthread_mutex_t));
	if (!forks)
		shinu(forks, stats, NULL, MALLOC_ERROR);
	while (i < stats->nbr_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free_forks(forks, i);
			shinu(forks, stats, NULL, MUTEX_ERROR);
		}
		i++;
	}
	return (forks);
}
