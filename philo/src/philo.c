/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:02:15 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/09/25 16:13:41 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_stats		stats;
	t_philo		*philo;
	pthread_mutex_t	*fork;

	if (!check_args(argc, argv) || !(build_struct(argv, &stats)))
		shinu(NULL, NULL, NULL, WRONG_ARGS);
	fork = init_forks(&stats);
	philo = init_philos(&stats, fork);
	/* if (!ft_startphilos(&philo))
		return (1); */
	return (0);
}
