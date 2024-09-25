/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:08:58 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/09/25 14:07:00 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(pthread_mutex_t *forks, int end)
{
	int	i;

	i = 0;
	while (i <= end)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	free_all(pthread_mutex_t *forks, t_stats *stats, t_philo *philo)
{
	int	i;

	i = 0;
	if (stats)
		pthread_mutex_destroy(&stats->mutex);
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
	if (forks)
	{
		while (i < stats->nbr_philo)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
		free(forks);
		forks = NULL;
	}
}

void	shinu(pthread_mutex_t *forks, t_stats *stats, t_philo *philo, char *error)
{
	free_all(forks, stats, philo);
	write(STDERR_FILENO, "ERROR: ", 7);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

