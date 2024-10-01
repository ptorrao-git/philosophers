/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:02:15 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/09/30 14:22:39 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_stats		stats;
	t_philo		*philo;
	pthread_mutex_t	*forks;

	if (!check_args(argc, argv) || !(build_struct(argv, &stats)))
		if(!shinu(NULL, NULL, NULL, WRONG_ARGS))
			return (1);
	forks = init_forks(&stats);
	philo = init_philos(&stats, forks);
	if (!start_thread(&stats, philo, forks))
		return (1);
	free_all(forks, &stats, philo);
	return (1);
}
