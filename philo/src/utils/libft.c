/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:28:43 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/09/30 16:50:44 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	t;

	i = 0;
	neg = 1;
	t = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		t = t * 10 + (str[i] - '0');
		i++;
	}
	t = t * neg;
	return (t);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

void	print_status(t_philo *philo, char *status, int action)
{
	suseconds_t	time;
	
	if (philo->stats->end == true && action != DEAD)
		return ;
	pthread_mutex_lock(&philo->stats->mutex);
	if (philo->stats->end == false)
	{
		time = get_time() - philo->start_time;
		printf("%ld %d %s\n", time, philo->philo_id, status);
	}
	else if (action == DEAD)
	{
		time = get_time() - philo->start_time;
		printf("%ld %d %s\n", time, philo->philo_id, status);
	}
	else
	{
		pthread_mutex_unlock(&philo->stats->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->stats->mutex);
}
