/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:10:17 by tgernez           #+#    #+#             */
/*   Updated: 2023/05/05 13:47:31 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_mutexes_philo(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	philo = vars->philos;
	i = 0;
	while (i < vars->nb_philo)
	{
		pthread_mutex_init(&philo->m_last_eat, NULL);
		pthread_mutex_init(&philo->fork, NULL);
		pthread_mutex_init(&philo->m_is_eating, NULL);
		philo = philo->next;
		++i;
	}
	return (true);
}

int	init_mutexes(t_vars *vars)
{
	pthread_mutex_init(&vars->synchro, NULL);
	pthread_mutex_init(&vars->m_end, NULL);
	pthread_mutex_init(&vars->m_ate_enough, NULL);
	return (init_mutexes_philo(vars));
}

static int	destroy_mutexes_philos(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	philo = vars->philos;
	i = 0;
	while (i < vars->nb_philo)
	{
		int ret_value;

		ret_value = pthread_mutex_destroy(&philo->m_last_eat);
		ret_value = pthread_mutex_destroy(&philo->fork);
		if (ret_value)
			printf("Philo %d couldn't destruct fork %d\n", philo->nb, ret_value);
		ret_value = pthread_mutex_destroy(&philo->m_is_eating);
		philo = philo->next;
		++i;
	}
	return (0);
}

int	destroy_mutexes(t_vars *vars)
{
	pthread_mutex_destroy(&vars->m_ate_enough);
	pthread_mutex_destroy(&vars->m_end);
	pthread_mutex_destroy(&vars->synchro);
	return (destroy_mutexes_philos(vars));
}
