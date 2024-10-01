/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:12:47 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/01 12:35:02 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *v_philo)
{
	t_philo *philo;

	philo = (t_philo *)v_philo;
	if (philo->stats->nbr_philo == 1)
	{
		print_status(philo, FORKING, FORK);
		return (NULL);
	}
	while (true)
		if (!cycle(philo))
			break;
	return (NULL);
}

void	do_something(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->stats->mutex);
	if (philo->stats->end == true)
	{
		pthread_mutex_unlock(&philo->stats->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->stats->mutex);;
	if (action == FORK)
		pick_forks(philo);
	else if (action == EAT)
	{
		pthread_mutex_lock(&philo->stats->mutex);
		philo->last_meal = get_time();
		philo->num_eat++;
		if (philo->stats->end == true)
		{
			pthread_mutex_unlock(&philo->stats->mutex);
			lay_forks(philo);
			return ;
		}
		pthread_mutex_unlock(&philo->stats->mutex);
	}
	else if (action == DEFORK)
		lay_forks(philo);
}

void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->stats->mutex);
	if (philo->stats->end == true)
	{
		pthread_mutex_unlock(&philo->stats->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->stats->mutex);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, FORKING, FORK);
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, FORKING, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, FORKING, FORK);
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, FORKING, FORK);
	}
}

void	lay_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		print_status(philo, DEFORKING, DEFORK);
		pthread_mutex_unlock(philo->r_fork);
		print_status(philo, DEFORKING, DEFORK);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		print_status(philo, DEFORKING, DEFORK);
		pthread_mutex_unlock(philo->l_fork);
		print_status(philo, DEFORKING, DEFORK);
	}
}

bool	cycle(t_philo *philo)
{
	pthread_mutex_lock(&philo->stats->mutex);
	if (philo->stats->end == true)
	{
		pthread_mutex_unlock(&philo->stats->mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->stats->mutex);
	do_something(philo, FORK);
	do_something(philo, EAT);
	print_status(philo, EATING, EAT);
	usleep(philo->stats->time_to_eat * 999);
	pthread_mutex_lock(&philo->stats->mutex);
	if (philo->stats->end == true)
	{
		lay_forks(philo);
		pthread_mutex_unlock(&philo->stats->mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->stats->mutex);
	do_something(philo, DEFORK);
	print_status(philo, SLEEPING, SLEEP);
	usleep(philo->stats->time_to_sleep * 999);
	print_status(philo, THINKING, THINK);
	return (true);
}
