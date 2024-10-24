/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:21:32 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/21 16:57:59 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_is_digit(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (argv[++i])
	{
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf(DIGIT_ONLY);
				return (false);
			}
		}
		j = -1;
	}
	if (!check_max_int(argv))
		return (false);
	return (true);
}

bool	build_struct(char **argv, t_stats *stats)
{
	stats->nbr_philo = ft_atol(argv[1]);
	stats->time_to_die = ft_atol(argv[2]);
	stats->time_to_eat = ft_atol(argv[3]);
	stats->time_to_sleep = ft_atol(argv[4]);
	stats->eat_times = -1;
	if (argv[5])
		stats->eat_times = ft_atol(argv[5]);
	if (stats->nbr_philo == 0 || stats->eat_times == 0
		|| stats->time_to_die == 0)
		return (false);
	if (pthread_mutex_init(&(stats->mutex), NULL) != 0)
	{
		shinu(NULL, stats, NULL, MUTEX_ERROR);
		return (false);
	}
	stats->end = false;
	return (true);
}

bool	check_args(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6) || !(check_is_digit(argv)))
		return (false);
	return (true);
}

bool	check_max_int(char **argv)
{
	if (ft_atol(argv[1]) > INT_MAX)
		return (false);
	if (ft_atol(argv[2]) > INT_MAX)
		return (false);
	if (ft_atol(argv[3]) > INT_MAX)
		return (false);
	if (ft_atol(argv[4]) > INT_MAX)
		return (false);
	if (argv[5])
		if (ft_atol(argv[5]) > INT_MAX)
			return (false);
	return (true);
}

bool	end_philo(t_stats *stats)
{
	pthread_mutex_lock(&stats->mutex);
	stats->end = true;
	pthread_mutex_unlock(&stats->mutex);
	return (true);
}
