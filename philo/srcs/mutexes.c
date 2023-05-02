/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:10:17 by tgernez           #+#    #+#             */
/*   Updated: 2023/05/02 16:10:17 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_mutexes_philo(t_vars *vars)
{
	int		i;
	int		ret_value;
	t_philo	*philo;

	philo = vars->philos;
	i = 0;
	while (i < vars->nb_philo)
	{
		ret_value = pthread_mutex_init(&philo->mutex_last_eat, NULL);
		if (ret_value)
			return (printf("Mutex LE failed code %d\n", ret_value));
		ret_value = pthread_mutex_init(&philo->fork, NULL);
		if (ret_value)
			return (printf("Mutex Fork failed code %d\n", ret_value));
		philo = philo->next;
		++i;
	}
	return (true);
}

int	init_mutexes(t_vars *vars)
{
	int		ret_value;

	ret_value = pthread_mutex_init(&vars->synchro, NULL);
	if (ret_value)
		return (printf("Mutex Synchro failed code %d\n", ret_value), ret_value);
	ret_value = pthread_mutex_init(&vars->mutex_end, NULL);
	if (ret_value)
		return (printf("Mutex End failed code %d\n", ret_value), ret_value);
	ret_value = pthread_mutex_init(&vars->mutex_ate_enough, NULL);
	if (ret_value)
		return (printf("Mutex Ate Egh failed code %d\n", ret_value), ret_value);
	return (init_mutexes_philo(vars));
}

static int	destroy_mutexes_philos(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	philo = vars->philos;
	i = 0;
	ft_usleep(10000);
	while (i < vars->nb_philo)
	{
		pthread_mutex_destroy(&philo->mutex_last_eat);
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
		++i;
	}
	return (0);
}

int	destroy_mutexes(t_vars *vars)
{
	int	ret_value;

	ret_value = pthread_mutex_destroy(&vars->mutex_ate_enough);
	if (ret_value)
		return (printf("Mut Dest AE Fail code %d\n", ret_value), ret_value);
	ret_value = pthread_mutex_destroy(&vars->mutex_end);
	if (ret_value)
		return (printf("Mut Dest End Fail code %d\n", ret_value), ret_value);
	ret_value = pthread_mutex_destroy(&vars->synchro);
	if (ret_value)
		return (printf("Mut Dest Sync Fail code %d\n", ret_value), ret_value);
	return (destroy_mutexes_philos(vars));
}
